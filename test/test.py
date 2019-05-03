import spvsdkpy as spv
def test_spvpy():
    print(spv)
    M = spv.PyMasterWalletManager("./Data")
    mne = M.GenerateMnemonic("english")
    print(mne)

    mw = M.CreateMasterWallet(
         masterWalletId='MasterWalletID',
         mnemonic=mne,
         phrasePassword='jkl;jkl;',
         payPassword='asdfasdf',
         singleAddress=False
     )

    print(mw)
    info = mw.GetBasicInfo()
    print(info)

test_spvpy()

