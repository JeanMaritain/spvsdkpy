import time
from manager import Manager


def case_create_hd_wallet():
    rootPath = "./Data"
    mgr = Manager(rootPath)
    mgr.load_from_local()
    wallet_counts = mgr.master_wallet_count
    if wallet_counts == 0:
        mgr.create_hd_wallet(
            lang="english",
            masterWalletId='MasterWalletID',
            phrasePassword='jkl;jkl;',
            payPassword='asdfasdf',
            singleAddress=False
        )
    time.sleep(100)


case_create_hd_wallet()
