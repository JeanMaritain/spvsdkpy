from typing import List, Dict
import spvsdkpy as spv
from tool import ctprint
from datetime import datetime
import json
import time


class SubWallet(object):
    def __init__(self, pysubwallet: spv.PySubWallet, master_wallet_id):
        self._master_wallet_id = master_wallet_id
        self._py_subwallet = pysubwallet
        self._call_back = SubWalletCallback(self)
        self._py_subwallet.AddCallback(self._call_back)

        self._h_current = None
        self._h_estimate = None
        self._t_last = None
        self._is_updated = False

        self._count_update_sync_process = None
        self._h_current_init = None
        self._h_estimate_init = None
        self._time_init_sync = None

        self.wait_sync_progress_cb(1)

    def send_tx(self, from_addr, to_addr, amount, memo, remark, use_voted_utxo, pay_psw, fee):
        tx_c = self._py_subwallet.CreateTransaction(from_addr, to_addr, amount, memo, remark, use_voted_utxo)
        ctprint(tx_c)
        _fee = self._py_subwallet.CalculateTransactionFee(tx_c, 10000)
        ctprint(fee)
        tx_fc = self._py_subwallet.UpdateTransactionFee(tx_c, _fee, from_addr)
        ctprint(tx_fc)
        tx_sfc = self._py_subwallet.SignTransaction(tx_fc, pay_psw)
        # tx_sc = self._py_subwallet.SignTransaction(tx_c, pay_psw)
        tx_res = self._py_subwallet.PublishTransaction(tx_sfc)
        ctprint(tx_res)
        cb_ = (
            self._call_back.count_on_tx_status_changed,
            self._call_back.count_on_tx_published,
            self._call_back.count_on_tx_deleted
        )
        cycle = 0
        while self._call_back.count_on_tx_status_changed == 0:
            ctprint(f"{cycle} {cb_}", end='\r')
            time.sleep(1)
            cycle += 1


    def get_balance(self):
        balance_type = spv.BalanceType
        balance_default = self._py_subwallet.GetBalance(balance_type.Default)
        balance_voted = self._py_subwallet.GetBalance(balance_type.Voted)
        balance_total = self._py_subwallet.GetBalance(balance_type.Total)
        return balance_default, balance_voted, balance_total

    def _print_member_var(self):
        for i, (k, v) in enumerate(self.__dict__.items()):
            if i < len(self.__dict__.items())-1:
                ctprint(k, end=':', t=False)
                ctprint(f"<{v}>", end='\n')
            else:
                ctprint(k, end='', t=False)
                ctprint(f"<{v}>")

    def wait_sync_progress_cb(self, count):
        t_begin = time.time()
        t_max = 360
        t = 0
        while t < t_max:
            ctprint(f"wait sync cb count {t}", end='\r')
            if self._call_back.count_on_block_sync_progress >= count:
                t_end = time.time()
                ctprint(f"[SYNC] C.B. no.{count} executed in {t_end - t_begin} sec")
                ctprint(f"waiting block_sync_progress, {self._count_update_sync_process}")
                break
            time.sleep(1)
            t += 1
        else:
            raise Exception(f"connecting_to_node timeout: {t_max}s")

    def wait_chains_sync(self, cycle_time=10):
        cycle = 0
        if self._h_estimate == self._h_estimate_init:
            self.wait_sync_progress_cb(2)

        while self._is_updated is False:
            ti = self._time_init_sync
            tn = int(time.time())
            _t = tn - ti

            hci = self._h_current_init
            hei = self._h_estimate_init
            _hi = hei - hci

            he = self._h_estimate
            hc = self._h_current
            _h = he - hc
            _he = he - hei
            _hc = hc - hci
            va_hc = _hc / _t

            l_h = _hi - _hc
            l_t = l_h / va_hc
            l_he_t = _he / va_hc
            l_t_ = _h / va_hc

            s2hms = (lambda sec: f"{int(sec/60/60)}:{int(sec/60%60)}:{int(sec%60)}({int(sec)}s)")
            if hc < hei:
                h_all = f"{_hi}+{_he}"
                info_r = f"{s2hms(l_t)}(+{int(l_he_t)}s) left."
            else:
                h_all = f"{_hi+_he}"
                info_r = f"about to complete... {l_t_}s left."

            info_h = f"sync stat: [{self.wallet_id}:{self.chain_id}] {cycle}({cycle_time}s): {_hc}/{h_all} completed "
            info_v = f"in {s2hms(_t)}s (v_avg:{int(va_hc)}blocks/s)"

            ctprint(f"{info_h} {info_v} {info_r}")
            time.sleep(cycle_time)
            cycle += 1

        ctprint(f'{self.wallet_id} now is updated')

    def get_addresses(self, from_=0, to=10):
        js_obj = json.loads(self._py_subwallet.GetAllAddress(from_, to))
        return js_obj

    @property
    def chain_id(self):
        return self._py_subwallet.GetChainID()

    @property
    def wallet_id(self):
        return self._master_wallet_id

    def update_sync_progress(self, current, estimate, block_time):
        self._h_current = current
        self._h_estimate = estimate
        self._t_last = block_time

        if self._count_update_sync_process is None:
            self._count_update_sync_process = 0
            self._h_current_init = current
            self._h_estimate_init = estimate
            self._time_init_sync = time.time()
        else:
            if current == estimate:
                self._is_updated = True
            elif current < estimate:
                self._is_updated = False
            else:
                raise Exception("current block height higher than the node")
        self._count_update_sync_process += 1


class SubWalletCallback(spv.IPySubWalletCallback):
    @staticmethod
    def _print_cb(cb_name, cb_info, cb_count, order=None):
        info = f" => {cb_info}" if not cb_info else cb_info
        text_to_print = f"{cb_count} [{order}-{cb_name}] {info}"
        return ctprint(text_to_print, t=False)

    def __init__(self, subwallet: SubWallet):
        super(SubWalletCallback, self).__init__()
        self.master = subwallet
        self.cid = self.master.chain_id
        self.wid = self.master.wallet_id
        self.id = f"{self.wid}:{self.cid}"

        self.count_on_tx_status_changed = 0
        self.count_on_block_sync_started = 0
        self.count_on_block_sync_progress = 0
        self.count_on_block_sync_stopped = 0
        self.count_on_balance_changed = 0
        self.count_on_tx_published = 0
        self.count_on_tx_deleted = 0
        self.count_on_asset_registered = 0

    def OnTransactionStatusChanged(self, tx_hash, status, desc, confirms):
        self.count_on_tx_status_changed += 1
        self._print_cb("OnTransactionStatusChanged", f"{tx_hash} | {status} | {desc} | {confirms}",
                       self.count_on_tx_status_changed, 1)

    def OnBlockSyncStarted(self):
        self.count_on_block_sync_started += 1
        self._print_cb("OnBlockSyncStarted", self.id, self.count_on_block_sync_started, 2)

    def OnBlockSyncProgress(self, current_block_height, estimated_height, last_block_time):
        self.count_on_block_sync_progress += 1
        _last_block_time = datetime.fromtimestamp(last_block_time).strftime('%Y-%m-%d %H:%M:%S')
        self._print_cb("OnBlockSyncProgress",
                       f"{self.id} {current_block_height}/{estimated_height} ({_last_block_time})",
                       self.count_on_block_sync_progress, 3)
        self.master.update_sync_progress(current_block_height, estimated_height, last_block_time)

    def OnBlockSyncStopped(self):
        self.count_on_block_sync_stopped += 1
        self._print_cb("OnBlockSyncStopped", self.id, self.count_on_block_sync_stopped, 4)

    def OnBalanceChanged(self, asset, balance):
        self.count_on_balance_changed += 1
        self._print_cb("OnBalanceChanged", f"{asset} | {balance}", self.count_on_balance_changed, 5)

    def OnTxPublished(self, hash_, result):
        self.count_on_tx_published += 1
        self._print_cb("OnTxPublished", f"{hash_} | {result}", self.count_on_tx_published, 6)

    def OnTxDeleted(self, hash_, notify_user, recommend_rescan):
        self.count_on_tx_deleted += 1
        self._print_cb("OnTxDeleted", hash_, self.count_on_tx_deleted, 7)

    def OnAssetRegistered(self, asset, info):
        self.count_on_asset_registered += 1
        self._print_cb("OnAssetRegistered", f"{asset} | {info}", self.count_on_asset_registered, 8)


class MasterWallet(object):
    def __init__(self, py_master_wallet: spv.PyMasterWallet):
        self._py_master_wallet = py_master_wallet
        self._wallet_id = self._py_master_wallet.GetID()

        self._sub_wallets_dict = {}
        self._load_sub_wallet()

        sub_wallets_number = len(self._sub_wallets_dict)
        ctprint(f"sub_wallets_number: {sub_wallets_number}")

        if sub_wallets_number == 0:
            new_py_sub_wallet = self._py_master_wallet.CreateSubWallet(chainID='ELA', feePerKb=10000)
            new_sub_wallet = SubWallet(new_py_sub_wallet, self._wallet_id)
            self._sub_wallets_dict[new_sub_wallet.chain_id] = new_sub_wallet

    def wait_sub_wallets_sync(self):
        for sw in self.sub_wallets_d.values():
            sw.wait_chains_sync()

    @property
    def sub_wallets_d(self):
        return self._sub_wallets_dict

    @property
    def wallet_id(self):
        return self._wallet_id

    def _load_sub_wallet(self):
        py_sub_wallets = self._py_master_wallet.GetAllSubWallets()
        for py_sub_wallet in py_sub_wallets:
            sub_wallet = SubWallet(py_sub_wallet, self._wallet_id)
            self._sub_wallets_dict[sub_wallet.chain_id] = sub_wallet


class Manager(object):
    def __init__(self, root_path):
        self._py_manager = spv.PyMasterWalletManager(root_path)
        self._master_wallets_dict = {}
        self._load_master_wallet()

    def wait_master_wallets_sync(self):
        for mw in self.master_wallets_d.values():
            mw.wait_sub_wallets_sync()

    def export_wallet_with_keystore(self, wid, backup_psw, pay_psw, with_prv_key):
        pymw = self.master_wallets_d[wid]._py_master_wallet
        ks = self._py_manager.ExportWalletWithKeystore(pymw, backup_psw, pay_psw, with_prv_key)
        ctprint(ks)

    def delete_wallet(self, wid):
        self._py_manager.DestoryWallet(wid)

    @property
    def master_wallet_number(self):
        return len(self._master_wallets_dict)

    @property
    def master_wallets_d(self) -> Dict[str, MasterWallet]:
        return self._master_wallets_dict

    def _load_master_wallet(self):
        py_master_wallets = self._py_manager.GetAllMasterWallets()
        if len(py_master_wallets) == 0:
            ctprint("no py_master_wallet loaded in local")
        for py_master_wallet in py_master_wallets:
            master_wallet = MasterWallet(py_master_wallet)
            self._master_wallets_dict[master_wallet.wallet_id] = master_wallet

    def import_wallet_with_mnemonic(self, wid, mnes, opt_psw, pay_psw, s_addr):
        py_master_wallet = self._py_manager.ImportWalletWithMnemonic(wid, mnes, opt_psw, pay_psw, s_addr)
        master_wallet = MasterWallet(py_master_wallet)
        self._master_wallets_dict[wid] = master_wallet

    def create_hd_wallet_mainchain(self, lang, wid, opt_psw, pay_psw, s_addr):
        _mnes = self._py_manager.GenerateMnemonic(lang)
        py_master_wallet = self._py_manager.CreateMasterWallet(wid, _mnes, opt_psw, pay_psw, s_addr)
        master_wallet = MasterWallet(py_master_wallet)
        self._master_wallets_dict[wid] = master_wallet

        py_master_wallet.CreateSubWallet(chainID="ELA", feePerKb=10000)
        return py_master_wallet
