// Copyright (c) 2012-2018 The Elastos Open Source Project
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef SPVSDKPY_EXCEPTIONFORMAT_H
#define SPVSDKPY_EXCEPTIONFORMAT_H

class ExceptionFormat {

public:
	typedef enum {
		InvalidArgument = 40000,
		NotMainchainSubWalletInstance = 40001,
		NotSidechainSubWalletInstance = 40002,
		NotTokenchainSubWalletInstance = 40003,
		SubWalletCallbackAlreadyRegistered = 40004,
		SubWalletCallbackNotRegistered = 40005,
		Other = 49999,
	} Code;

public:
	static nlohmann::json MakeErrorJson(Code code, const std::string &msg) {
		nlohmann::json j;
		j["Code"] = code;
		j["Message"] = msg;
		return j;
	}

	static void Throw(Code code, const std::string &msg) {
		nlohmann::json errJson = MakeErrorJson(code, msg);
		throw std::logic_error(errJson.dump());
	}

	static void Check(bool condition, Code code, const std::string &msg) {
		if (condition) {
			Throw(code, msg);
		}
	}

};

#endif //SPVSDKPY_EXCEPTIONFORMAT_H
