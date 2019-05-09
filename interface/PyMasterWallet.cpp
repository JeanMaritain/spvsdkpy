#include "PyMasterWallet.h"

PyMasterWallet::PyMasterWallet() :
        _masterWallet(nullptr) {
}

PyMasterWallet::PyMasterWallet(IMasterWallet *masterWallet) :
        _masterWallet(masterWallet) {
}

std::string PyMasterWallet::GetID() const {
    return _masterWallet->GetId();
}

std::string PyMasterWallet::GetBasicInfo() const {
    return _masterWallet->GetBasicInfo().dump();
}

std::vector<PySubWallet> PyMasterWallet::GetAllSubWallets() const {
    std::vector<ISubWallet *> subWallets = _masterWallet->GetAllSubWallets();
    std::vector<PySubWallet> pySubWalelts;

    for (size_t i = 0; i < subWallets.size(); ++i)
        pySubWalelts.push_back(PySubWallet(subWallets[i]));

    return pySubWalelts;
}

PySubWallet PyMasterWallet::CreateSubWallet(const std::string &chainID, uint64_t feePerKb) {
    return PySubWallet(_masterWallet->CreateSubWallet(chainID, feePerKb));
}

void PyMasterWallet::DestroyWallet(const PySubWallet &subWallet) {
    return _masterWallet->DestroyWallet(subWallet.GetRaw());
}

std::string PyMasterWallet::GetPublicKey() const {
    return _masterWallet->GetPublicKey();
}

std::string PyMasterWallet::Sign(const std::string &message, const std::string &payPassword) {
    return _masterWallet->Sign(message, payPassword);
}

bool PyMasterWallet::CheckSign(const std::string &publicKey, const std::string &message, const std::string &signature) {
    return _masterWallet->CheckSign(publicKey, message, signature);
}

bool PyMasterWallet::IsAddressValid(const std::string &address) const {
    return _masterWallet->IsAddressValid(address);
}

std::vector<std::string> PyMasterWallet::GetSupportedChains() const {
    return _masterWallet->GetSupportedChains();
}

void PyMasterWallet::ChangePassword(const std::string &oldPassword, const std::string &newPassword) {
    _masterWallet->ChangePassword(oldPassword, newPassword);
}
