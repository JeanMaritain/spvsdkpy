// Copyright (c) 2012-2018 The Elastos Open Source Project
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef SPVSDKPY_PYMAINCHAINSUBWALLET_H
#define SPVSDKPY_PYMAINCHAINSUBWALLET_H

#include "IMainchainSubWallet.h"
#include "PySubWallet.h"

using namespace Elastos::ElaWallet;

class PyMainchainSubWallet : public PySubWallet {
public:
	explicit PyMainchainSubWallet(const PySubWallet &subWallet);
	/**
	 * Virtual destructor.
	 */
	virtual ~PyMainchainSubWallet() noexcept {}

	/**
	 * Create a deposit transaction and return the content of transaction in json format. Note that \p amount should greater than sum of \p so that we will leave enough fee for sidechain.
	 * @param fromAddress specify which address we want to spend, or just input empty string to let wallet choose UTXOs automatically.
	 * @param toAddress specify which address we want to send, in this method to address shall be genesis address of the side chain
	 * @param amount specify amount we want to send.
	 * @param sidechainAccounts a list of sidechain accounts in json format.
	 * @param sidechainAmounts a list of sidechain amounts in json format, each amount should correspond to \p sidechainAccounts by order.
	 * @param sidechainIndices a list of sidechain indices in json format, each index should correspond to \p sidechainAccounts by order.
	 * @param memo input memo attribute for describing.
	 * @param remark is used to record message of local wallet.
	 * @return　If success return the content of transaction in json format.
	 */
	virtual std::string CreateDepositTransaction(
		const std::string &fromAddress,
		const std::string &lockedAddress,
		uint64_t amount,
		const std::string &sideChainAddress,
		const std::string &memo,
		const std::string &remark,
		bool useVotedUTXO = false);

	virtual std::string GenerateProducerPayload(
		const std::string &publicKey,
		const std::string &nodePublicKey,
		const std::string &nickName,
		const std::string &url,
		const std::string &ipAddress,
		uint64_t location,
		const std::string &payPasswd) const;

	virtual std::string GenerateCancelProducerPayload(
		const std::string &publicKey,
		const std::string &payPasswd) const;

	virtual std::string CreateRegisterProducerTransaction(
		const std::string &fromAddress,
		const std::string &payload,
		uint64_t amount,
		const std::string &memo,
		const std::string &remark,
		bool useVotedUTXO = false);

	virtual std::string CreateUpdateProducerTransaction(
		const std::string &fromAddress,
		const std::string &payload,
		const std::string &memo,
		const std::string &remark,
		bool useVotedUTXO = false);

	virtual std::string CreateCancelProducerTransaction(
		const std::string &fromAddress,
		const std::string &payload,
		const std::string &memo,
		const std::string &remark,
		bool useVotedUTXO = false);

	virtual std::string CreateRetrieveDepositTransaction(
		uint64_t amount,
		const std::string &memo,
		const std::string &remark);

	virtual std::string GetPublicKeyForVote() const;

	virtual std::string CreateVoteProducerTransaction(
		const std::string &fromAddress,
		uint64_t stake,
		const std::string &pubicKeys,
		const std::string &memo,
		const std::string &remark,
		bool useVotedUTXO = false);

	virtual	std::string GetVotedProducerList() const;

	virtual std::string GetRegisteredProducerInfo() const;

private:
	IMainchainSubWallet *_mainchainSubWallet;
};


#endif //SPVSDKPY_PYMAINCHAINSUBWALLET_H
