// Copyright (c) 2012-2019 The Elastos Open Source Project
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef SPVSDKPY_PYSUBWALLETCALLBACK_H
#define SPVSDKPY_PYSUBWALLETCALLBACK_H

#include "IPySubWalletCallback.h"
#include <pybind11/pybind11.h>

class PySubWalletCallback : IPySubWalletCallback {
public:
	PySubWalletCallback() {}

	~PySubWalletCallback() {}
	/**
	 * Callback method fired when status of a transaction changed.
	 * @param txid indicate hash of the transaction.
	 * @param status can be "Added", "Deleted" or "Updated".
	 * @param desc is an detail description of transaction status.
	 * @param confirms is confirm count util this callback fired.
	 */
	 // FIXME complete here
	 virtual void OnTransactionStatusChanged(
		 const std::string &txid,
		 const std::string &status,
		 const std::string &desc,
		 uint32_t confirms) {}

	/**
	 * Callback method fired when block begin synchronizing with a peer. This callback could be used to show progress.
	 */
	virtual void OnBlockSyncStarted() {}

	/**
	 * Callback method fired when best block chain height increased. This callback could be used to show progress.
	 * @param currentBlockHeight is the of current block when callback fired.
	 * @param estimatedHeight is max height of blockchain.
	 * @param lastBlockTime timestamp of the last block.
	 */
	virtual void OnBlockSyncProgress(uint32_t currentBlockHeight, uint32_t estimatedHeight, time_t lastBlockTime) {}

	/**
	 * Callback method fired when block end synchronizing with a peer. This callback could be used to show progress.
	 */
	virtual void OnBlockSyncStopped() {}

	virtual void OnBalanceChanged(const std::string &asset, const std::string &balance) {}

	virtual void OnTxPublished(const std::string &hash, const std::string &result) {}

	virtual void OnTxDeleted(const std::string &hash, bool notifyUser, bool recommendRescan) {}

	virtual void OnAssetRegistered(const std::string &asset, const std::string &info) {}
};


#endif //SPVSDKPY_PYSUBWALLETCALLBACK_H
