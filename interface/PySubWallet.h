// Copyright (c) 2012-2018 The Elastos Open Source Project
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef SPVSDKPY_PYSUBWALLET_H
#define SPVSDKPY_PYSUBWALLET_H

#include <ISubWallet.h>
#include "SubWalletCallback.h"

using namespace Elastos::ElaWallet;

class PySubWallet {
public:
	PySubWallet();

	explicit PySubWallet(ISubWallet *subWallet);

	virtual ~PySubWallet() {}

	ISubWallet *GetRaw() const {
		return _subWallet;
	}

	SubWalletCallback *GetRawCallback() const {
		return _subCallback;
	}

	/**
	 * Get the sub wallet chain id.
	 * @return sub wallet chain id.
	 */
	virtual std::string GetChainID() const;

	/**
	 * Here is a example of hd account wallet basic info:
	 * {
	 * 	"Type": "Normal" //Type can be Normal, Mainchain, Sidechain and Idchain
	 * 	"Account":
	 * 		{
	 * 			"Type": "HD Account"
	 * 			"Details":
	 * 				{
	 * 					"CoinIndex": 1
	 * 				}
	 * 		}
	 * }
	 *
	 * and an example of multi-sign account wallet basic info:
	 * {
	 * 	"Type": "Mainchain" //Type can be Normal, Mainchain, Sidechain and Idchain
	 * 	"Account":
	 * 		{
	 * 			"Type": "Multi-Sign Account"
	 * 		}
	 * }
	 * @return basic information of current master wallet.
	 */
	virtual std::string GetBasicInfo() const;

	/**
	 * Get balances of all addresses in json format.
	 * @return balances of all addresses in json format.
	 */
	virtual std::string GetBalanceInfo() const;

	/**
	 * Get sum of balances of all addresses according to balance type.
	 * @return sum of balances.
	 */
	virtual uint64_t GetBalance(BalanceType type = Default) const;

	/**
	 * Get balance of only the specified address.
	 * @param address is one of addresses created by current sub wallet.
	 * @return balance of specified address.
	 */
	virtual uint64_t GetBalanceWithAddress(const std::string &address, BalanceType type = Default) const;

	/**
	 * Create a new address or return existing unused address. Note that if create the sub wallet by setting the singleAddress to true, will always return the single address.
	 * @return a new address or existing unused address.
	 */
	virtual std::string CreateAddress();

	/**
	 * Get all created addresses in json format. The parameters of start and count are used for purpose of paging.
	 * @param start specify start index of all addresses list.
	 * @param count specify count of addresses we need.
	 * @return addresses in json format.
	 */
	virtual std::string GetAllAddress(
		uint32_t start,
		uint32_t count) const;

	/**
	 * Add a sub wallet callback object listened to current sub wallet.
	 * @param subCallback is a pointer who want to listen events of current sub wallet.
	 */
	virtual void AddCallback(IPySubWalletCallback *callback);

	/**
	 * Remove a sub wallet callback object listened to current sub wallet.
	 * @param subCallback is a pointer who want to listen events of current sub wallet.
	 */
	virtual void RemoveCallback();

	/**
	 * Create a normal transaction and return the content of transaction in json format.
	 * @param fromAddress specify which address we want to spend, or just input empty string to let wallet choose UTXOs automatically.
	 * @param toAddress specify which address we want to send.
	 * @param amount specify amount we want to send.
	 * @param memo input memo attribute for describing.
	 * @param remark is used to record message of local wallet.
	 * @return If success return the content of transaction in json format.
	 */
	virtual std::string CreateTransaction(
		const std::string &fromAddress,
		const std::string &toAddress,
		uint64_t amount,
		const std::string &memo,
		const std::string &remark,
		bool useVotedUTXO = false);

	/**
	 * Calculate transaction fee by content of transaction.
	 * @param rawTransaction content of transaction in json format.
	 * @param feePerKb specify the factor to calculate fee (transaction size * feePerKb).
	 * @return Calculate result of final fee.
	 */
	virtual uint64_t CalculateTransactionFee(
		const std::string &tx,
		uint64_t feePerKb);

	/**
	 * Update a transaction by change fee
	 * @param transactionJson content of transaction in json format.
	 * @param fee specify fee for miners, fee must greater or equal than 1000 (sela).
	 * @return Sent result in json format.
	 */
	virtual std::string UpdateTransactionFee(
		const std::string &tx,
		uint64_t fee,
		const std::string &fromAddress);

	/**
	 * Sign a transaction or append sign to a multi-sign transaction and return the content of transaction in json format.
	 * @param rawTransaction content of transaction in json format.
	 * @param payPassword use to decrypt the root private key temporarily. Pay password should between 8 and 128, otherwise will throw invalid argument exception.
	 * @return If success return the content of transaction in json format.
	 */
	virtual std::string SignTransaction(
		const std::string &tx,
		const std::string &payPassword);

	/**
	 * Get signers already signed specified transaction.
	 * @param rawTransaction a multi-sign transaction to find signed signers.
	 * @return Signed signers in json format. An example of result will be displayed as follows:
	 *
	 * [{"M":3,"N":4,"SignType":"MultiSign","Signers":["02753416fc7c1fb43c91e29622e378cd16243b53577ec971c6c3624a775722491a","0370a77a257aa81f46629865eb8f3ca9cb052fcfd874e8648cfbea1fbf071b0280","030f5bdbee5e62f035f19153c5c32966e0fc72e419c2b4867ba533c43340c86b78"]}]
	 * or
	 * [{"SignType":"Standard","Signers":["028e0ce09c7a5905f876f38473d4e1e0a85327122372e5db14fc72f88311c30e75"]}]
	 *
	 */
	virtual std::string GetTransactionSignedSigners(
		const std::string &tx) const;

	/**
	 * Send a transaction by p2p network.
	 * @param rawTransaction content of transaction in json format.
	 * @param fee specify fee for miners, fee must greater or equal than 1000 (sela).
	 * @return Sent result in json format.
	 */
	virtual std::string PublishTransaction(
		const std::string &tx);

	/**
	 * Get all qualified transactions sorted by descent (newest first).
	 * @param start specify start index of all transactions list.
	 * @param count specify count of transactions we need.
	 * @param addressOrTxid filter word which can be an address or a transaction id, if empty all transactions shall be qualified.
	 * @return All qualified transactions in json format.
	 */
	virtual std::string GetAllTransaction(
		uint32_t start,
		uint32_t count,
		const std::string &addressOrTxid) const;

	/**
	 * Sign message through root private key of the master wallet.
	 * @param message need to signed, it should not be empty.
	 * @param payPassword use to decrypt the root private key temporarily. Pay password should between 8 and 128, otherwise will throw invalid argument exception.
	 * @return signed data of the message.
	 */
	virtual std::string Sign(
		const std::string &message,
		const std::string &payPassword);

	/**
	 * Verify signature by public key and raw message. This method can check signatures signed by any private keys not just the root private key of the master wallet.
	 * @param publicKey belong to the private key signed the signature.
	 * @param message raw data.
	 * @param signature signed data by a private key that correspond to the public key.
	 * @return true or false.
	 */
	virtual bool CheckSign(
		const std::string &publicKey,
		const std::string &message,
		const std::string &signature);

	/**
	 * Get an asset details by specified asset ID
	 * @param assetID asset hex code from asset hash.
	 * @return asset info in json format.
	 */
	virtual std::string GetAssetInfo(
		const std::string &assetID) const;

	/**
	 * Get root public key of current sub wallet.
	 * @return root public key with hex string format.
	 */
	virtual std::string GetPublicKey() const;

protected:
	ISubWallet *_subWallet;
	SubWalletCallback *_subCallback;
};


#endif //SPVSDKPY_PYSUBWALLET_H
