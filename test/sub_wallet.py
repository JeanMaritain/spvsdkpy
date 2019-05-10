import spvsdkpy as spv


class SubWallet(spv.IPySubWalletCallback):
    def __init__(self, pysubwallet: spv.PySubWallet):
        super(SubWallet, self).__init__()
        self._call_back = self
        self._pysubwallet = pysubwallet
        self._pysubwallet.AddCallback(self._call_back)

        self._current_block_height = 0
        self._estimate_block_height = 0
        self._last_block_time = 0

    def update_sync_progress(self, current, estimate, time):
        self._current_block_height = current
        self._estimate_block_height = estimate
        self._last_block_time = time

    def OnTransactionStatusChanged(self, txHash, status, desc, confirms):
        print("[OnTransactionStatusChanged] => %s | %s | %ld" % (txHash, status, confirms))

    def OnBlockSyncStarted(self):
        print("[OnBlockSyncStarted]")

    def OnBlockSyncProgress(self, currentBlockHeight, estimatedHeight, lastBlockTime):
        print("[OnBlockSyncProgress] => %d / %d (%d)" % (currentBlockHeight, estimatedHeight, lastBlockTime))
        self.update_sync_progress(currentBlockHeight, estimatedHeight, lastBlockTime)

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
