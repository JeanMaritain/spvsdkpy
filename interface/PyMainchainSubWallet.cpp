// Copyright (c) 2012-2018 The Elastos Open Source Project
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <IMainchainSubWallet.h>
#include "PyMainchainSubWallet.h"
#include "ExceptionFormat.h"

PyMainchainSubWallet::PyMainchainSubWallet(const PySubWallet &subWallet) {
	IMainchainSubWallet *mainchainSubWallet = dynamic_cast<IMainchainSubWallet *>(subWallet.GetRaw());
	if (mainchainSubWallet == nullptr) {
		ExceptionFormat::Throw(ExceptionFormat::NotMainchainSubWalletInstance,
							   "subWallet is not instance of IMainchainSubWallet");
	}

	_subWallet = subWallet.GetRaw();
	_subCallback = subWallet.GetRawCallback();
	_mainchainSubWallet = mainchainSubWallet;
}

std::string
PyMainchainSubWallet::CreateDepositTransaction(const std::string &fromAddress, const std::string &lockedAddress,
											   uint64_t amount, const std::string &sideChainAddress,
											   const std::string &memo, const std::string &remark, bool useVotedUTXO) {
	return _mainchainSubWallet->CreateDepositTransaction(fromAddress, lockedAddress, amount, sideChainAddress,
														 memo, remark, useVotedUTXO).dump();
}

std::string
PyMainchainSubWallet::GenerateProducerPayload(const std::string &publicKey, const std::string &nodePublicKey,
											  const std::string &nickName, const std::string &url,
											  const std::string &ipAddress, uint64_t location,
											  const std::string &payPasswd) const {
	return _mainchainSubWallet->GenerateProducerPayload(publicKey, nodePublicKey, nickName, url,
														ipAddress, location, payPasswd).dump();
}

std::string
PyMainchainSubWallet::GenerateCancelProducerPayload(const std::string &publicKey, const std::string &payPasswd) const {
	return _mainchainSubWallet->GenerateCancelProducerPayload(publicKey, payPasswd).dump();
}

std::string
PyMainchainSubWallet::CreateRegisterProducerTransaction(const std::string &fromAddress, const std::string &payload,
														uint64_t amount, const std::string &memo,
														const std::string &remark, bool useVotedUTXO) {
	return _mainchainSubWallet->CreateRegisterProducerTransaction(fromAddress, nlohmann::json::parse(payload), amount,
																  memo, remark, useVotedUTXO).dump();
}

std::string
PyMainchainSubWallet::CreateUpdateProducerTransaction(const std::string &fromAddress, const std::string &payload,
													  const std::string &memo, const std::string &remark,
													  bool useVotedUTXO) {
	return _mainchainSubWallet->CreateUpdateProducerTransaction(fromAddress, nlohmann::json::parse(payload),
																memo, remark, useVotedUTXO).dump();
}

std::string
PyMainchainSubWallet::CreateCancelProducerTransaction(const std::string &fromAddress, const std::string &payload,
													  const std::string &memo, const std::string &remark,
													  bool useVotedUTXO) {
	return _mainchainSubWallet->CreateCancelProducerTransaction(fromAddress, nlohmann::json::parse(payload),
																memo, remark, useVotedUTXO).dump();
}

std::string PyMainchainSubWallet::CreateRetrieveDepositTransaction(uint64_t amount, const std::string &memo,
																	  const std::string &remark) {
	return _mainchainSubWallet->CreateRetrieveDepositTransaction(amount, memo, remark).dump();
}

std::string PyMainchainSubWallet::GetPublicKeyForVote() const {
	return _mainchainSubWallet->GetPublicKeyForVote();
}

std::string PyMainchainSubWallet::CreateVoteProducerTransaction(const std::string &fromAddress, uint64_t stake,
																const std::string &pubicKeys,
																const std::string &memo, const std::string &remark,
																bool useVotedUTXO) {
	return _mainchainSubWallet->CreateVoteProducerTransaction(fromAddress, stake, nlohmann::json::parse(pubicKeys),
															  memo, remark, useVotedUTXO).dump();
}

std::string PyMainchainSubWallet::GetVotedProducerList() const {
	return _mainchainSubWallet->GetVotedProducerList().dump();
}

std::string PyMainchainSubWallet::GetRegisteredProducerInfo() const {
	return _mainchainSubWallet->GetRegisteredProducerInfo().dump();
}


