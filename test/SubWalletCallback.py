import spvsdkpy as spv

class SubWalletCallback(spv.IPySubWalletCallback):
    def OnTransactionStatusChanged(self, txHash, status, desc, confirms):
        print("[OnTransactionStatusChanged] => %s | %s | %ld" % (txHash, status, confirms))

    def OnBlockSyncStarted(self):
        print("[OnBlockSyncStarted]")

    def OnBlockSyncProgress(self, currentBlockHeight, estimatedHeight, lastBlockTime):
        print("[OnBlockSyncProgress] => %d / %d (%d)" % (currentBlockHeight, estimatedHeight, lastBlockTime))

    def OnBlockSyncStopped(self):
        print("[OnBlockSyncStopped]")

    def OnBalanceChanged(self, asset, balance):
        print("[OnBalanceChanged] => %s | %s" % (asset, balance))

    def OnTxPublished(self, hash, result):
        print("[OnTxPublished] => %s | %s" % (hash, result))

    def OnTxDeleted(self, hash, notifyUser, recommendRescan):
        print("[OnTxDeleted] => %s" % hash)

    def OnAssetRegistered(self, asset, info):
        print("[OnAssetRegistered] => %s | %s" % (asset, info))