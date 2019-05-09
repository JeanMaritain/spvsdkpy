#include <MasterWalletManager.h>
#include <nlohmann/json.hpp>
#include "PyMasterWallet.h"
#include "PyMasterWalletManager.h"


using namespace Elastos::ElaWallet;

PyMasterWalletManager::PyMasterWalletManager(const std::string &rootPath) {
    _mwm = new MasterWalletManager(rootPath);
}

PyMasterWalletManager::~PyMasterWalletManager() {
    delete _mwm;
}

void PyMasterWalletManager::SaveConfigs() {

}

std::string PyMasterWalletManager::GenerateMnemonic(const std::string &language) const {
    return _mwm->GenerateMnemonic(language);
}

std::string
PyMasterWalletManager::GetMultiSignPubKey(const std::string &phrase, const std::string &phrasePassword) const {
    return _mwm->GetMultiSignPubKey(phrase, phrasePassword);

}

PyMasterWallet PyMasterWalletManager::CreateMasterWallet(const std::string &masterWalletId, const std::string &mnemonic,
                                                         const std::string &phrasePassword,
                                                         const std::string &payPassword, bool singleAddress) {
    return PyMasterWallet(_mwm->CreateMasterWallet(masterWalletId, mnemonic, phrasePassword, payPassword, singleAddress));
}

PyMasterWallet PyMasterWalletManager::CreateMultiSignMasterWalletReadOnly(const std::string &masterWalletId,
        const std::string &coSigners, uint32_t requiredSignCount) {
    return PyMasterWallet(_mwm->CreateMultiSignMasterWallet(masterWalletId,
                                                            nlohmann::json::parse(coSigners),
                                                            requiredSignCount));
}

PyMasterWallet PyMasterWalletManager::CreateMultiSignMasterWallet(const std::string &masterWalletId, const std::string &mnemonic,
                                                   const std::string &phrasePassword, const std::string &payPassword,
                                                   const std::string &coSigners, uint32_t requiredSignCount) {
    IMasterWallet *ptr = _mwm->CreateMultiSignMasterWallet(masterWalletId,
                                                           mnemonic,
                                                           phrasePassword,
                                                           payPassword,
                                                           nlohmann::json::parse(coSigners),
                                                           requiredSignCount);
    return PyMasterWallet(ptr);
}

std::vector<PyMasterWallet> PyMasterWalletManager::GetAllMasterWallets() const {
	std::vector<PyMasterWallet> pyMasterWallets;
	std::vector<IMasterWallet *> masterWallets = _mwm->GetAllMasterWallets();
	for (size_t i = 0; i < masterWallets.size(); ++i) {
	    pyMasterWallets.push_back(PyMasterWallet(masterWallets[i]));
	}
    return pyMasterWallets;
}

std::vector<std::string> PyMasterWalletManager::GetAllMasterWalletIds() const {
    return _mwm->GetAllMasterWalletIds();
}

PyMasterWallet PyMasterWalletManager::GetWallet(const std::string &masterWalletId) const {
    return PyMasterWallet(_mwm->GetWallet(masterWalletId));
}

void PyMasterWalletManager::DestroyWallet(const std::string &masterWalletId) {
    return _mwm->DestroyWallet(masterWalletId);
}

PyMasterWallet
PyMasterWalletManager::ImportWalletWithKeystore(const std::string &masterWalletId, const std::string &keystoreContent,
                                                const std::string &backupPassword, const std::string &payPassword) {
    nlohmann::json keystore = nlohmann::json::parse(keystoreContent);
    return PyMasterWallet(_mwm->ImportWalletWithKeystore(masterWalletId, keystore, backupPassword, payPassword));
}

PyMasterWallet
PyMasterWalletManager::ImportWalletWithMnemonic(const std::string &masterWalletId, const std::string &mnemonic,
                                                const std::string &phrasePassword, const std::string &payPassword,
                                                bool singleAddress) {
    return PyMasterWallet(_mwm->ImportWalletWithMnemonic(masterWalletId, mnemonic, phrasePassword, payPassword, singleAddress));
}

std::string
PyMasterWalletManager::ExportWalletWithKeystore(const PyMasterWallet &masterWallet, const std::string &backupPassword,
                                                const std::string &payPassword, bool withPrivKey) const {

    return _mwm->ExportWalletWithKeystore(masterWallet.GetRaw(), backupPassword, payPassword, withPrivKey).dump();
}

std::string
PyMasterWalletManager::ExportWalletWithMnemonic(const PyMasterWallet &masterWallet, const std::string &payPassword) const {
    return _mwm->ExportWalletWithMnemonic(masterWallet.GetRaw(), payPassword);
}

std::string PyMasterWalletManager::GetVersion() const {
    return _mwm->GetVersion();
}

std::string PyMasterWalletManager::EncodeTransactionToString(const std::string &tx) {
    nlohmann::json txJson = nlohmann::json::parse(tx);
    return _mwm->EncodeTransactionToString(txJson).dump();
}

std::string PyMasterWalletManager::DecodeTransactionFromString(const std::string &cipher) {
    nlohmann::json cipherJson = nlohmann::json::parse(cipher);
    return _mwm->DecodeTransactionFromString(cipherJson).dump();
}


