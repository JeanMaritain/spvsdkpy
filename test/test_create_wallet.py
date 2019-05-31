import unittest
from ddt import ddt, data, unpack

from tool import backup_file, ctprint, clear_spv_local_data_and_logfile
import sys


def prepare_spv_module():
    SPV_BIN_DIR = "~/CLionProjects/spvsdkpy/cmake-build-debug"
    SPV_BIN_NAME = "spvsdkpy.cpython-37m-darwin.so"
    MODULE_PATH = "./lib"
    backup_file(SPV_BIN_DIR, SPV_BIN_NAME, MODULE_PATH)
    sys.path.append(MODULE_PATH)


prepare_spv_module()
from client import Manager


class DataPath(object):
    MainNet = "./Data/Data_MN"
    RegNet = "./Data/Data_RN"
    TestNet = "./Data/Data_TN"
    MainNetTemp0 = "./Data/Temp/Data_MN_0"
    MainNetTemp1 = "./Data/Temp/Data_MN_1"
    RegNetTempXC = "./Data/Temp/Data_RN_XC"


def t_create_and_sync(root_path, wid, lang, opt_psw, pay_psw, s_addr):
    cid = 'ELA'
    clear_spv_local_data_and_logfile(root_path, wid)
    manager = Manager(root_path)
    manager.create_hd_wallet_mainchain(lang, wid, opt_psw, pay_psw, s_addr)
    sw_ela = manager.master_wallets_d[wid].sub_wallets_d[cid]
    ctprint(sw_ela.get_addresses())
    manager.wait_master_wallets_sync()


class SpvPythonWalletTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls) -> None:
        cls.root_path = DataPath.TestNet

    def setUp(self) -> None:
        self.wid = "TEST_CREATE_AND_SYNC"
        self.lang = "english"
        self.opt_psw = "jkl;jkl;"
        self.pay_psw = "asdfasdf"
        self.s_addr = False

    def test_create_and_sync(self):
        t_create_and_sync(self.root_path, self.wid, self.lang, self.opt_psw, self.pay_psw, self.s_addr)



if __name__ == "__main__":
    case_list = [
        SpvPythonWalletTest,
    ]
    suite = [unittest.TestLoader().loadTestsFromTestCase(case) for case in case_list]
    unittest.TextTestRunner(verbosity=2).run(unittest.TestSuite(suite))
