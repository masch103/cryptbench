#ifndef CRYPTOINTERFACE_HASHFUNCTION_FACTORY_H_
#define CRYPTOINTERFACE_HASHFUNCTION_FACTORY_H_

#include <memory>
#include <vector>

#include "hashfunction.h"

namespace CryptoInterface {

using hashPointer = std::unique_ptr<CryptoInterface::HashFunction>;
using functionVector = std::vector<std::string>;

static functionVector supportedHashfunctions { "MD5", "RIPEMD160", "SHA1",
		"SHA224", "SHA256", "SHA384", "SHA512", "SHA3-224", "SHA3-256",
		"SHA3-384", "SHA3-512", "Whirlpool10" };

class HashFunctionFactory {
public:
	HashFunctionFactory();
	static hashPointer createHashfunction(const std::string& name);
	~HashFunctionFactory();
};

} /* namespace CryptoInterface */

#endif /* CRYPTOINTERFACE_HASHFUNCTION_FACTORY_H_ */
