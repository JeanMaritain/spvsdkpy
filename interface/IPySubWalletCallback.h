// Copyright (c) 2012-2018 The Elastos Open Source Project
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef SPVSDKPY_IPYSUBWALLETCALLBACK_H
#define SPVSDKPY_IPYSUBWALLETCALLBACK_H

#include <string>

class IPySubWalletCallback {
public:
	virtual ~IPySubWalletCallback() noexcept {}

	/**
	 * Callback method fired when status of a transaction changed.
	 * @param txid indicate hash of the transaction.
	 * @param status can be "Added", "Deleted" or "Updated".
	 * @param desc is an detail description of transaction status.
	 * @param confirms is confirm count util this callback fired.
	 */
	virtual void OnTransactionStatusChanged(
		const std::string &txid,
		const std::string &status,
		const std::string &desc,
		uint32_t confirms) = 0;

	/**
	 * Callback method fired when block begin synchronizing with a peer. This callback could be used to show progress.
	 */
	virtual void OnBlockSyncStarted() = 0;

	/**
	 * Callback method fired when best block chain height increased. This callback could be used to show progress.
	 * @param currentBlockHeight is the of current block when callback fired.
	 * @param estimatedHeight is max height of blockchain.
	 * @param lastBlockTime timestamp of the last block.
	 */
	virtual void OnBlockSyncProgress(uint32_t currentBlockHeight, uint32_t estimatedHeight, time_t lastBlockTime) = 0;

	/**
	 * Callback method fired when block end synchronizing with a peer. This callback could be used to show progress.
	 */
	virtual void OnBlockSyncStopped() = 0;

	virtual void OnBalanceChanged(const std::string &asset, const std::string &balance) = 0;

	virtual void OnTxPublished(const std::string &hash, const std::string &result) = 0;

	virtual void OnTxDeleted(const std::string &hash, bool notifyUser, bool recommendRescan) = 0;

	virtual void OnAssetRegistered(const std::string &asset, const std::string &info) = 0;

};

#endif //SPVSDKPY_IPYSUBWALLETCALLBACK_H
