// Copyright (c) 2012-2018 The Elastos Open Source Project
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "SubWalletCallback.h"
#include <pybind11/pybind11.h>

namespace py = pybind11;

namespace Elastos {
    namespace ElaWallet {

        SubWalletCallback::SubWalletCallback(IPySubWalletCallback *callback) {
        	_callback = callback;
        }

        SubWalletCallback::~SubWalletCallback() {

        }


        void SubWalletCallback::OnTransactionStatusChanged(const std::string &txid,
                                                           const std::string &status,
                                                           const nlohmann::json &desc,
                                                           uint32_t confirms) {
                _callback->OnTransactionStatusChanged(txid, status, desc.dump(), confirms);
        }

        void SubWalletCallback::OnBlockSyncStarted() {
                _callback->OnBlockSyncStarted();
        }

        void SubWalletCallback::OnBlockSyncProgress(uint32_t currentBlockHeight,
                                                    uint32_t estimatedHeight,
                                                    time_t lastBlockTime) {
                _callback->OnBlockSyncProgress(currentBlockHeight, estimatedHeight, lastBlockTime);
        }

        void SubWalletCallback::OnBlockSyncStopped() {
                _callback->OnBlockSyncStopped();
        }

        void SubWalletCallback::OnBalanceChanged(const std::string &asset, const std::string &balance) {
                _callback->OnBalanceChanged(asset, balance);
        }

        void
        SubWalletCallback::OnTxPublished(const std::string &hash, const nlohmann::json &result) {
                _callback->OnTxPublished(hash, result.dump());
        }

        void SubWalletCallback::OnTxDeleted(const std::string &hash, bool notifyUser, bool recommendRescan) {
                _callback->OnTxDeleted(hash, notifyUser, recommendRescan);
        }
        void SubWalletCallback::OnAssetRegistered(const std::string &asset, const nlohmann::json &info) {
                _callback->OnAssetRegistered(asset, info.dump());
        }

    }
}
