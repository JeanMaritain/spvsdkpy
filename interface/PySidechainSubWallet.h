// Copyright (c) 2012-2018 The Elastos Open Source Project
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef SPVSDKPY_PYSIDECHAINSUBWALLET_H
#define SPVSDKPY_PYSIDECHAINSUBWALLET_H

#include <ISidechainSubWallet.h>
#include "PySubWallet.h"

class PySidechainSubWallet : PySubWallet {
public:
	explicit PySidechainSubWallet(const PySubWallet &subWallet);
	/**
	 * Virtual destructor.
	 */
	virtual ~PySidechainSubWallet() noexcept {}

	/**
	 * Create a withdraw transaction and return the content of transaction in json format. Note that \p amount should greater than sum of \p so that we will leave enough fee for mainchain.
	 * @param fromAddress specify which address we want to spend, or just input empty string to let wallet choose UTXOs automatically.
	 * @param amount specify amount we want to send.
	 * @param mainchainAccounts a list of mainchain accounts in json format.
	 * @param mainchainAmounts a list of mainchain amounts in json format, each amount should correspond to \p mainchainAccounts by order.
	 * @param mainchainIndexs a list of mainchain indices in json format, each index should correspond to \p mainchainAccounts by order.
	 * @param memo input memo attribute for describing.
	 * @param remark is used to record message of local wallet.
	 * @return If success return the content of transaction in json format.
	 */
	virtual std::string CreateWithdrawTransaction(
		const std::string &fromAddress,
		uint64_t amount,
		const std::string &mainChainAddress,
		const std::string &memo,
		const std::string &remark);

	/**
	 * Get genesis address of the side chain, the address is a special address will be set to toAddress in CreateDepositTransaction.
	 * @return genesis address of the side chain.
	 */
	virtual std::string GetGenesisAddress() const;

private:
	ISidechainSubWallet *_sidechainSubWallet;
};


#endif //SPVSDKPY_PYSIDECHAINSUBWALLET_H
