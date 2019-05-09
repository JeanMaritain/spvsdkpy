// Copyright (c) 2012-2018 The Elastos Open Source Project
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "PySubWallet.h"
#include "PySubWalletCallback.h"
#include "ExceptionFormat.h"

PySubWallet::PySubWallet() :
	_subWallet(nullptr),
	_subCallback(nullptr) {

}

PySubWallet::PySubWallet(ISubWallet *subWallet) :
	_subWallet(subWallet),
	_subCallback(nullptr) {

}

std::string PySubWallet::GetChainID() const {
	return _subWallet->GetChainId();
}

std::string PySubWallet::GetBasicInfo() const {
	return _subWallet->GetBasicInfo().dump();
}

std::string PySubWallet::GetBalanceInfo() const {
	return _subWallet->GetBalanceInfo().dump();
}

uint64_t PySubWallet::GetBalance(BalanceType type) const {
	return _subWallet->GetBalance(type);
}

uint64_t PySubWallet::GetBalanceWithAddress(const std::string &address, BalanceType type) const {
	return _subWallet->GetBalanceWithAddress(address, type);
}

std::string PySubWallet::CreateAddress() {
	return _subWallet->CreateAddress();
}

std::string PySubWallet::GetAllAddress(uint32_t start, uint32_t count) const {
	return _subWallet->GetAllAddress(start, count).dump();
}

void PySubWallet::AddCallback(IPySubWalletCallback *callback) {
	if (_subCallback != nullptr) {
		ExceptionFormat::Throw(ExceptionFormat::SubWalletCallbackAlreadyRegistered,
							   "subWallet callback have already registered");
	}
	_subCallback = new SubWalletCallback(callback);
	_subWallet->AddCallback(_subCallback);
}

void PySubWallet::RemoveCallback() {
	if (_subCallback == nullptr) {
		ExceptionFormat::Throw(ExceptionFormat::SubWalletCallbackNotRegistered,
							   "subWallet remove callback fail: not registered");
	}

	_subWallet->RemoveCallback(_subCallback);
	delete _subCallback;
	_subCallback = nullptr;
}

std::string
PySubWallet::CreateTransaction(const std::string &fromAddress, const std::string &toAddress, uint64_t amount,
							   const std::string &memo, const std::string &remark, bool useVotedUTXO) {
	return _subWallet->CreateTransaction(fromAddress, toAddress, amount, memo, remark, useVotedUTXO).dump();
}

uint64_t PySubWallet::CalculateTransactionFee(const std::string &tx, uint64_t feePerKb) {
	return _subWallet->CalculateTransactionFee(nlohmann::json::parse(tx), feePerKb);
}

std::string
PySubWallet::UpdateTransactionFee(const std::string &tx, uint64_t fee, const std::string &fromAddress) {
	return _subWallet->UpdateTransactionFee(nlohmann::json::parse(tx), fee, fromAddress).dump();
}

std::string PySubWallet::SignTransaction(const std::string &tx, const std::string &payPassword) {
	return _subWallet->SignTransaction(nlohmann::json::parse(tx), payPassword).dump();
}

std::string PySubWallet::GetTransactionSignedSigners(const std::string &tx) const {
	return _subWallet->GetTransactionSignedSigners(nlohmann::json::parse(tx)).dump();
}

std::string PySubWallet::PublishTransaction(const std::string &tx) {
	return _subWallet->PublishTransaction(nlohmann::json::parse(tx)).dump();
}

std::string PySubWallet::GetAllTransaction(uint32_t start, uint32_t count, const std::string &addressOrTxid) const {
	return _subWallet->GetAllTransaction(start, count, addressOrTxid).dump();
}

std::string PySubWallet::Sign(const std::string &message, const std::string &payPassword) {
	return _subWallet->Sign(message, payPassword);
}

bool PySubWallet::CheckSign(const std::string &publicKey, const std::string &message, const std::string &signature) {
	return _subWallet->CheckSign(publicKey, message, signature);
}

std::string PySubWallet::GetAssetInfo(const std::string &assetID) const {
	return _subWallet->GetAssetInfo(assetID).dump();
}

std::string PySubWallet::GetPublicKey() const {
	return _subWallet->GetPublicKey();
}

