// Copyright (c) 2012-2018 The Elastos Open Source Project
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "PySidechainSubWallet.h"
#include "ExceptionFormat.h"

PySidechainSubWallet::PySidechainSubWallet(const PySubWallet &subWallet) {
	ISidechainSubWallet *sidechainSubWallet = dynamic_cast<ISidechainSubWallet *>(subWallet.GetRaw());
	if (sidechainSubWallet == nullptr) {
		ExceptionFormat::Throw(ExceptionFormat::NotSidechainSubWalletInstance,
							   "subWallet is not instance of ISidechainSubWallet");
	}

	_subWallet = subWallet.GetRaw();
	_subCallback = subWallet.GetRawCallback();
	_sidechainSubWallet = sidechainSubWallet;
}

std::string PySidechainSubWallet::CreateWithdrawTransaction(const std::string &fromAddress, uint64_t amount,
															const std::string &mainChainAddress,
															const std::string &memo, const std::string &remark) {
	return _sidechainSubWallet->CreateWithdrawTransaction(fromAddress, amount, mainChainAddress, memo, remark).dump();
}

std::string PySidechainSubWallet::GetGenesisAddress() const {
	return _sidechainSubWallet->GetGenesisAddress();
}
