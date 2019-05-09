import spvsdkpy as spv
import SubWalletCallback as cb
import time

def CreateWallet(manager):
    mnemonic = manager.GenerateMnemonic("english")
    masterWallet = manager.CreateMasterWallet(
        masterWalletId='MasterWalletID',
        mnemonic=mnemonic,
        phrasePassword='jkl;jkl;',
        payPassword='asdfasdf',
        singleAddress=False)

    subWallet = masterWallet.CreateSubWallet("ELA", 10000)

    return masterWallet

def test_spvpy():
    manager = spv.PyMasterWalletManager("./Data")
    masterWallets = manager.GetAllMasterWallets()

    if len(masterWallets) == 0:
        masterWallet = CreateWallet(manager)
        masterWallets[0] = masterWallet

    callback = cb.SubWalletCallback()
    for mWallet in masterWallets:
        subWallets = mWallet.GetAllSubWallets()
        for subWallet in subWallets:
            subWallet.AddCallback(callback)

    time.sleep(120)

test_spvpy()

