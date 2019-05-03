#include "PyMasterWallet.h"

PyMasterWallet::PyMasterWallet() :
        _masterWallet(nullptr) {
}

PyMasterWallet::PyMasterWallet(IMasterWallet *masterWallet) :
        _masterWallet(masterWallet) {
}

std::string PyMasterWallet::GetId() const {
    return std::string();
}

std::string PyMasterWallet::GetBasicInfo() const {
    return _masterWallet->GetBasicInfo().dump();
}

std::vector<ISubWallet *> PyMasterWallet::GetAllSubWallets() const {
    return std::vector<ISubWallet *>();
}

ISubWallet *PyMasterWallet::CreateSubWallet(const std::string &chainID, uint64_t feePerKb) {
    return nullptr;
}

void PyMasterWallet::DestroyWallet(ISubWallet *wallet) {

}

std::string PyMasterWallet::GetPublicKey() const {
    return std::string();
}

std::string PyMasterWallet::Sign(const std::string &message, const std::string &payPassword) {
    return std::string();
}

bool PyMasterWallet::CheckSign(const std::string &publicKey, const std::string &message, const std::string &signature) {
    return false;
}

bool PyMasterWallet::IsAddressValid(const std::string &address) const {
    return false;
}

std::vector<std::string> PyMasterWallet::GetSupportedChains() const {
    return std::vector<std::string>();
}

void PyMasterWallet::ChangePassword(const std::string &oldPassword, const std::string &newPassword) {

}
