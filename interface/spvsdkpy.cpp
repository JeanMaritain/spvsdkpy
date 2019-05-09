// Copyright (c) 2012-2019 The Elastos Open Source Project
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "PyMasterWalletManager.h"
#include "PyMasterWallet.h"
#include "PySubWallet.h"
#include "PySubWalletCallback.h"
#include "PySidechainSubWallet.h"
#include "PyTokenchainSubWallet.h"
#include "PyMainchainSubWallet.h"

#include <iostream>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;
using namespace pybind11::literals;


PYBIND11_MODULE(spvsdkpy, m){
    m.doc() = "example of spv sdk pybind11 interface, add PyMasterWalletManager";

    py::class_<PyMasterWalletManager>(m, "PyMasterWalletManager")
        .def(py::init<const std::string &>())
        .def("SaveConfigs", &PyMasterWalletManager::SaveConfigs)
        .def("GenerateMnemonic", &PyMasterWalletManager::GenerateMnemonic, "langrage"_a)
        .def("GetMultiSignPubKey", &PyMasterWalletManager::GetMultiSignPubKey, "phrase"_a, "phrasePassword"_a)
        .def("CreateMasterWallet", &PyMasterWalletManager::CreateMasterWallet,
             "masterWalletId"_a,
             "mnemonic"_a,
             "phrasePassword"_a,
             "payPassword"_a,
             "singleAddress"_a)
        .def("CreateMultiSignMasterWalletReadOnly", &PyMasterWalletManager::CreateMultiSignMasterWalletReadOnly,
             "masterWalletId"_a,
             "coSigners"_a,
             "requiredSignCount"_a)
        .def("CreateMultiSignMasterWallet", &PyMasterWalletManager::CreateMultiSignMasterWallet,
             "masterWalletId"_a,
             "mnemonic"_a,
             "phrasePassword"_a,
             "payPassword"_a,
             "coSigners"_a,
             "requiredSignCount"_a)
        .def("GetAllMasterWallets", &PyMasterWalletManager::GetAllMasterWallets)
        .def("GetAllMasterWalletIds", &PyMasterWalletManager::GetAllMasterWalletIds)
        .def("GetWallet", &PyMasterWalletManager::GetWallet, "masterWalletId"_a)
        .def("DestoryWallet", &PyMasterWalletManager::DestroyWallet, "masterWalletId"_a)
        .def("ImportWalletWithKeystore", &PyMasterWalletManager::ImportWalletWithKeystore,
             "masterWalletId"_a,
             "keystoreContent"_a,
             "backupPassword"_a,
             "payPassword"_a)
        .def("ImportWalletWithMnemonic", &PyMasterWalletManager::ImportWalletWithMnemonic,
             "masterWalletId"_a,
             "mnemonic"_a,
             "phrasePassword"_a,
             "payPassword"_a,
             "singleAddress"_a)
        .def("ExportWalletWithKeystore", &PyMasterWalletManager::ExportWalletWithKeystore,
             "masterWalletId"_a,
             "backupPassword"_a,
             "payPassword"_a,
             "withPrivKey"_a)
        .def("ExportWalletWithMnemonic", &PyMasterWalletManager::ExportWalletWithMnemonic,
             "masterWalletId"_a,
             "payPassword"_a)
        .def("GetVersion", &PyMasterWalletManager::GetVersion)
        .def("EncodeTransactionToString", &PyMasterWalletManager::EncodeTransactionToString, "tx"_a)
        .def("DecodeTransactionFromString", &PyMasterWalletManager::DecodeTransactionFromString, "cipher"_a);

    py::class_<PyMasterWallet>(m, "PyMasterWallet")
        .def(py::init<>())
        .def("GetID", &PyMasterWallet::GetID)
        .def("GetBasicInfo", &PyMasterWallet::GetBasicInfo)
        .def("GetAllSubWallets", &PyMasterWallet::GetAllSubWallets)
        .def("CreateSubWallet", &PyMasterWallet::CreateSubWallet,
             "chainID"_a,
             "feePerKb"_a)
        .def("DestroyWallet", &PyMasterWallet::DestroyWallet,
             "subWallet"_a)
        .def("GetPublicKey", &PyMasterWallet::GetPublicKey)
        .def("Sign", &PyMasterWallet::Sign,
             "message"_a,
             "payPassword"_a)
        .def("CheckSign", &PyMasterWallet::CheckSign,
             "publicKey"_a,
             "message"_a,
             "signature"_a)
        .def("IsAddressValid", &PyMasterWallet::IsAddressValid,
            "address"_a)
        .def("GetSupportedChains", &PyMasterWallet::GetSupportedChains)
        .def("ChangePassword", &PyMasterWallet::ChangePassword,
            "oldPassword"_a,
             "newPassword"_a);

    py::class_<PySubWallet>(m, "PySubWallet")
        .def(py::init<>())
		.def("GetChainID", &PySubWallet::GetChainID)
		.def("GetBasicInfo", &PySubWallet::GetBasicInfo)
		.def("GetBalanceInfo", &PySubWallet::GetBalanceInfo)
		.def("GetBalance", &PySubWallet::GetBalance,
			 "type"_a)
		.def("GetBalanceWithAddress", &PySubWallet::GetBalanceWithAddress,
			 "address"_a,
			 "type"_a)
		.def("CreateAddress", &PySubWallet::CreateAddress)
		.def("GetAllAddress", &PySubWallet::GetAllAddress,
			 "start"_a,
			 "count"_a)
		.def("AddCallback", &PySubWallet::AddCallback,
			 "callback"_a)
		.def("RemoveCallback", &PySubWallet::RemoveCallback)
		.def("CreateTransaction", &PySubWallet::CreateTransaction,
			 "fromAddress"_a,
			 "toAddress"_a,
			 "amount"_a,
			 "memo"_a,
			 "remark"_a,
			 "useVotedUTXO"_a)
		.def("CalculateTransactionFee", &PySubWallet::CalculateTransactionFee,
			 "tx"_a,
			 "feePerKb"_a)
		.def("UpdateTransactionFee", &PySubWallet::UpdateTransactionFee,
			 "tx"_a,
			 "fee"_a,
			 "fromAddress"_a)
		.def("SignTransaction", &PySubWallet::SignTransaction,
			 "tx"_a,
			 "payPassword"_a)
		.def("GetTransactionSignedSigners", &PySubWallet::GetTransactionSignedSigners,
			 "tx"_a)
		.def("PublishTransaction", &PySubWallet::PublishTransaction,
			 "tx"_a)
		.def("GetAllTransaction", &PySubWallet::GetAllTransaction,
			 "start"_a,
			 "count"_a,
			 "addressOrTxid"_a)
		.def("Sign", &PySubWallet::Sign,
			 "message"_a,
			 "payPassword"_a)
		.def("CheckSign", &PySubWallet::CheckSign,
			 "publicKey"_a,
			 "message"_a,
			 "signature"_a)
		.def("GetAssetInfo", &PySubWallet::GetAssetInfo,
			 "assetID"_a)
		.def("GetPublicKey", &PySubWallet::GetPublicKey);

    py::class_<IPySubWalletCallback, PySubWalletCallback>(m, "IPySubWalletCallback")
        .def(py::init<>())
		.def("OnTransactionStatusChanged", &IPySubWalletCallback::OnTransactionStatusChanged)
    	.def("OnBlockSyncStarted", &IPySubWalletCallback::OnBlockSyncStarted)
		.def("OnBlockSyncProgress", &IPySubWalletCallback::OnBlockSyncProgress)
		.def("OnBlockSyncStopped", &IPySubWalletCallback::OnBlockSyncStopped)
		.def("OnBalanceChanged", &IPySubWalletCallback::OnBalanceChanged)
		.def("OnTxPublished", &IPySubWalletCallback::OnTxPublished)
		.def("OnTxDeleted", &IPySubWalletCallback::OnTxDeleted)
		.def("OnAssetRegistered", &IPySubWalletCallback::OnAssetRegistered);

    py::class_<PyMainchainSubWallet>(m, "PyMainchainSubWallet")
        .def(py::init<const PySubWallet &>())
		.def("CreateDepositTransaction", &PyMainchainSubWallet::CreateDepositTransaction,
			 "fromAddress"_a,
			 "lockedAddress"_a,
			 "amount"_a,
			 "sideChainAddress"_a,
			 "memo"_a,
			 "remark"_a,
			 "useVotedUTXO"_a)
		.def("GenerateProducerPayload", &PyMainchainSubWallet::GenerateProducerPayload,
			 "publicKey"_a,
			 "nodePublicKey"_a,
			 "nickName"_a,
			 "url"_a,
			 "ipAddress"_a,
			 "location"_a,
			 "payPasswd"_a)
		.def("GenerateCancelProducerPayload", &PyMainchainSubWallet::GenerateCancelProducerPayload,
			 "publicKey"_a,
			 "payPasswd"_a)
		.def("CreateRegisterProducerTransaction", &PyMainchainSubWallet::CreateRegisterProducerTransaction,
			 "fromAddress"_a,
			 "payload"_a,
			 "amount"_a,
			 "memo"_a,
			 "remark"_a,
			 "useVotedUTXO"_a)
		.def("CreateUpdateProducerTransaction", &PyMainchainSubWallet::CreateUpdateProducerTransaction,
			 "fromAddress"_a,
			 "payload"_a,
			 "memo"_a,
			 "remark"_a,
			 "useVotedUTXO"_a)
		.def("CreateCancelProducerTransaction", &PyMainchainSubWallet::CreateCancelProducerTransaction,
			 "fromAddress"_a,
			 "payload"_a,
			 "memo"_a,
			 "remark"_a,
			 "useVotedUTXO"_a)
		.def("CreateRetrieveDepositTransaction", &PyMainchainSubWallet::CreateRetrieveDepositTransaction,
			 "amount"_a,
			 "memo"_a,
			 "remark"_a)
		.def("GetPublicKeyForVote", &PyMainchainSubWallet::GetPublicKeyForVote)
		.def("CreateVoteProducerTransaction", &PyMainchainSubWallet::CreateVoteProducerTransaction,
			 "fromAddress"_a,
			 "stake"_a,
			 "pubicKeys"_a,
			 "memo"_a,
			 "remark"_a,
			 "useVotedUTXO"_a)
		.def("GetVotedProducerList", &PyMainchainSubWallet::GetVotedProducerList)
		.def("GetRegisteredProducerInfo", &PyMainchainSubWallet::GetRegisteredProducerInfo);

    py::class_<PySidechainSubWallet>(m, "PySidechainSubWallet")
        .def(py::init<const PySubWallet &>())
		.def("CreateWithdrawTransaction", &PySidechainSubWallet::CreateWithdrawTransaction,
			 "fromAddress"_a,
			 "amount"_a,
			 "mainChainAddress"_a,
			 "memo"_a,
			 "remark"_a)
		.def("GetGenesisAddress", &PySidechainSubWallet::GetGenesisAddress);

    py::class_<PyTokenchainSubWallet>(m, "PyTokenchainSubWallet")
        .def(py::init<const PySubWallet &>())
		.def("GetBalanceInfo", &PyTokenchainSubWallet::GetBalanceInfo,
			 "assetID"_a)
		.def("GetBalance", &PyTokenchainSubWallet::GetBalance,
			 "assetID"_a)
		.def("GetBalanceWithAddress", &PyTokenchainSubWallet::GetBalanceWithAddress,
			 "assetID"_a,
			 "address"_a)
		.def("CreateRegisterAssetTransaction", &PyTokenchainSubWallet::CreateRegisterAssetTransaction,
			 "name"_a,
			 "description"_a,
			 "registerToAddress"_a,
			 "registerAmount"_a,
			 "precision"_a,
			 "memo"_a,
			 "remark"_a)
		.def("CreateTransaction", &PyTokenchainSubWallet::CreateTransaction,
			 "fromAddress"_a,
			 "toAddress"_a,
			 "amount"_a,
			 "assetID"_a,
			 "memo"_a,
			 "remark)"_a)
		.def("GetAllAssets", &PyTokenchainSubWallet::GetAllAssets);

}
