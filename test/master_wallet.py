import spvsdkpy as spv
from sub_wallet import SubWallet

class MasterWallet(object):
    def __init__(self, pymasterwallet: spv.PyMasterWallet):
        self._py_master_wallet = pymasterwallet

        if len(self._py_master_wallet.GetAllSubWallets()) == 0:
            self._py_master_wallet.CreateSubWallet(chainID="ELA", feePerKb=10000)

        self._subWallets = [SubWallet(py_sub_wallet)
            for py_sub_wallet in self._py_master_wallet.GetAllSubWallets()]


    @property
    def master_wallet(self):
        return self._py_master_wallet

    @master_wallet.setter
    def master_wallet(self, masterwallet):
        self._py_master_wallet = masterwallet
