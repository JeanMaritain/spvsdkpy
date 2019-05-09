// Copyright (c) 2012-2019 The Elastos Open Source Project
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef SPVSDKPY_PYSUBWALLETCALLBACK_H
#define SPVSDKPY_PYSUBWALLETCALLBACK_H

#include "IPySubWalletCallback.h"
#include <pybind11/pybind11.h>

class PySubWalletCallback : IPySubWalletCallback {
public:
	using IPySubWalletCallback::IPySubWalletCallback;

	~PySubWalletCallback() {}
	/**
	 * Callback method fired when status of a transaction changed.
	 * @param txid indicate hash of the transaction.
	 * @param status can be "Added", "Deleted" or "Updated".
	 * @param desc is an detail description of transaction status.
	 * @param confirms is confirm count util this callback fired.
	 */
	 void OnTransactionStatusChanged(
		 const std::string &txHash,
		 const std::string &status,
		 const std::string &desc,
		 uint32_t confirms) override {
		PYBIND11_OVERLOAD_PURE(void, IPySubWalletCallback, OnTransactionStatusChanged, txHash, status, desc, confirms);
	 }

	/**
	 * Callback method fired when block begin synchronizing with a peer. This callback could be used to show progress.
	 */
	void OnBlockSyncStarted() override {
		PYBIND11_OVERLOAD_PURE(void, IPySubWalletCallback, OnBlockSyncStarted);
	}

	/**
	 * Callback method fired when best block chain height increased. This callback could be used to show progress.
	 * @param currentBlockHeight is the of current block when callback fired.
	 * @param estimatedHeight is max height of blockchain.
	 * @param lastBlockTime timestamp of the last block.
	 */
	void OnBlockSyncProgress(uint32_t currentBlockHeight, uint32_t estimatedHeight, time_t lastBlockTime) override {
		PYBIND11_OVERLOAD_PURE(void, IPySubWalletCallback, OnBlockSyncProgress, currentBlockHeight, estimatedHeight, lastBlockTime);
	}

	/**
	 * Callback method fired when block end synchronizing with a peer. This callback could be used to show progress.
	 */
	void OnBlockSyncStopped() override {
		PYBIND11_OVERLOAD_PURE(void, IPySubWalletCallback, OnBlockSyncStopped);
	}

	void OnBalanceChanged(const std::string &asset, const std::string &balance) override {
		PYBIND11_OVERLOAD_PURE(void, IPySubWalletCallback, OnBalanceChanged, asset, balance);
	}

	void OnTxPublished(const std::string &hash, const std::string &result) override {
		PYBIND11_OVERLOAD_PURE(void, IPySubWalletCallback, OnTxPublished, hash, result);
	}

	void OnTxDeleted(const std::string &hash, bool notifyUser, bool recommendRescan) override {
		PYBIND11_OVERLOAD_PURE(void, IPySubWalletCallback, OnTxDeleted, hash, notifyUser, recommendRescan);
	}

	void OnAssetRegistered(const std::string &asset, const std::string &info) override {
		PYBIND11_OVERLOAD_PURE(void, IPySubWalletCallback, OnAssetRegistered, asset, info);
	}
};


#endif //SPVSDKPY_PYSUBWALLETCALLBACK_H
