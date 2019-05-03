#include <iostream>

#include <pybind11/pybind11.h>

#include "PyMasterWalletManager.h"
#include "PySubWalletCallback.h"
#include "PyMasterWallet.h"

namespace py = pybind11;
using namespace pybind11::literals;


PYBIND11_MODULE(spvsdkpy, m){
    m.doc() = "example of spv sdk pybind11 interface, add PyMasterWalletManager";

    py::class_<PyMasterWallet>(m, "PyMasterWallet")
            .def(py::init<>())
            .def("GetBasicInfo", &PyMasterWallet::GetBasicInfo);

    py::class_<PySubWalletCallback>(m, "PySubWalletCallback")
            .def(py::init<const std::string &, const std::string &>());

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
}
