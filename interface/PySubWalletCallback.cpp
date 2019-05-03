// Copyright (c) 2012-2018 The Elastos Open Source Project
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "PySubWalletCallback.h"
#include <pybind11/pybind11.h>

namespace py = pybind11;

namespace Elastos {
    namespace ElaWallet {

        PySubWalletCallback::PySubWalletCallback(const std::string &masterWalletID, const std::string &subWalletID) {
            _masterWalletID = masterWalletID;
            _subWalletID = subWalletID;
        }

        PySubWalletCallback::~PySubWalletCallback() {

        }


        void PySubWalletCallback::OnTransactionStatusChanged(const std::string &txid,
                                                           const std::string &status,
                                                           const nlohmann::json &desc,
                                                           uint32_t confirms) {

            py::object callback = py::module::import("SubWalletCallback");
            py::object OnTransactionStatusChangedCB = callback.attr("OnTransactionStatusChanged");

            OnTransactionStatusChangedCB(_masterWalletID, _subWalletID, txid, status, desc.dump(), confirms);
        }

        void PySubWalletCallback::OnBlockSyncStarted() {
            py::object callback = py::module::import("SubWalletCallback");
            py::object OnBlockSyncStartedCB = callback.attr("OnBlockSyncStarted");

            OnBlockSyncStartedCB(_masterWalletID, _subWalletID);
        }

        void PySubWalletCallback::OnBlockSyncProgress(uint32_t currentBlockHeight,
                                                    uint32_t estimatedHeight,
                                                    time_t lastBlockTime) {

        }

        void PySubWalletCallback::OnBlockSyncStopped() {

        }

        void PySubWalletCallback::OnBalanceChanged(const std::string &asset, const std::string &balance) {

        }

        void
        PySubWalletCallback::OnTxPublished(const std::string &hash, const nlohmann::json &result) {

        }

        void PySubWalletCallback::OnTxDeleted(const std::string &hash, bool notifyUser, bool recommendRescan) {

        }
        void PySubWalletCallback::OnAssetRegistered(const std::string &asset, const nlohmann::json &info) {
 
        }

    }
}
