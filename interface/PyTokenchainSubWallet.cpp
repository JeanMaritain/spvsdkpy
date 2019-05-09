// Copyright (c) 2012-2018 The Elastos Open Source Project
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "PyTokenchainSubWallet.h"
#include "ExceptionFormat.h"

PyTokenchainSubWallet::PyTokenchainSubWallet(const PySubWallet &subWallet) {
	ITokenchainSubWallet *tokenchainSubWallet = dynamic_cast<ITokenchainSubWallet *>(subWallet.GetRaw());
	if (tokenchainSubWallet == nullptr)
		ExceptionFormat::Throw(ExceptionFormat::NotTokenchainSubWalletInstance,
							   "subWallet is not instance of ITokenchainSubWallet");

	_subWallet = subWallet.GetRaw();
	_subCallback = subWallet.GetRawCallback();
	_tokenchainSubWallet = tokenchainSubWallet;
}

std::string PyTokenchainSubWallet::GetBalanceInfo(const std::string &assetID) const {
	return _tokenchainSubWallet->GetBalanceInfo(assetID).dump();
}

std::string PyTokenchainSubWallet::GetBalance(const std::string &assetID) const {
	return _tokenchainSubWallet->GetBalance(assetID);
}

std::string PyTokenchainSubWallet::GetBalanceWithAddress(const std::string &assetID, const std::string &address) const {
	return _tokenchainSubWallet->GetBalanceWithAddress(assetID, address);
}

std::string
PyTokenchainSubWallet::CreateRegisterAssetTransaction(const std::string &name, const std::string &description,
													  const std::string &registerToAddress, uint64_t registerAmount,
													  uint8_t precision, const std::string &memo,
													  const std::string &remark) {
	return _tokenchainSubWallet->CreateRegisterAssetTransaction(name, description, registerToAddress,
																registerAmount, precision, memo, remark).dump();
}

std::string PyTokenchainSubWallet::CreateTransaction(const std::string &fromAddress, const std::string &toAddress,
													 const std::string &amount, const std::string &assetID,
													 const std::string &memo, const std::string &remark) {
	return _tokenchainSubWallet->CreateTransaction(fromAddress, toAddress, amount, assetID, memo, remark).dump();
}

std::string PyTokenchainSubWallet::GetAllAssets() const {
	return _tokenchainSubWallet->GetAllAssets().dump();
}
