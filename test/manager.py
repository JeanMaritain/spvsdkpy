import spvsdkpy as spv
from master_wallet import MasterWallet


class Manager(object):
    def __init__(self, rootPath):
        self._py_manager = spv.PyMasterWalletManager(rootPath)
        self._masterWallets = []

    @property
    def master_wallet_count(self):
        return len(self._masterWallets)

    def load_from_local(self):
        self._masterWallets = [MasterWallet(py_master_wallet)
            for py_master_wallet in self._py_manager.GetAllMasterWallets()]

    def create_hd_wallet(self,
                         lang="english",
                         masterWalletId='MasterWalletID',
                         phrasePassword='jkl;jkl;',
                         payPassword='asdfasdf',
                         singleAddress=False):
        mnemonics = self._py_manager.GenerateMnemonic(lang)
        masterWallet = self._py_manager.CreateMasterWallet(
            masterWalletId=masterWalletId,
            mnemonic=mnemonics,
            phrasePassword=phrasePassword,
            payPassword=payPassword,
            singleAddress=singleAddress)

        self._masterWallets.append(MasterWallet(masterWallet))

        masterWallet.CreateSubWallet(chainID="ELA", feePerKb=10000)
        return masterWallet




