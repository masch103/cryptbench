#include "hashfunction_factory.h"
#include "md5.h"
#include "ripemd160.h"
#include "sha1.h"
#include "sha224_256.h"
#include "sha384_512.h"
#include "sha3.h"
#include "whirlpool.h"
#include "hash_utility.h"
#include <iostream>

namespace CryptoInterface {

HashFunctionFactory::HashFunctionFactory() {
}

HashFunctionFactory::~HashFunctionFactory() {
}

hashPointer HashFunctionFactory::createHashfunction(const std::string& name) {
	if (name == "MD5") {
		return std::make_unique<CryptoInterface::MessageDigest5>();
	} else if (name == "SHA1") {
		return std::make_unique<CryptoInterface::Sha1>();
	} else if (name == "SHA224") {
		return std::make_unique < CryptoInterface::Sha224_256 > (224);
	} else if (name == "SHA256") {
		return std::make_unique < CryptoInterface::Sha224_256 > (256);
	} else if (name == "SHA384") {
		return std::make_unique < CryptoInterface::Sha384_512 > (384);
	} else if (name == "SHA512") {
		return std::make_unique < CryptoInterface::Sha384_512 > (512);
	} else if (name == "RIPEMD160") {
		return std::make_unique<CryptoInterface::Ripemd160>();
	} else if (name == "SHA3-224") {
		return std::make_unique < CryptoInterface::Sha3 > (224);
	} else if (name == "SHA3-256") {
		return std::make_unique < CryptoInterface::Sha3 > (256);
	} else if (name == "SHA3-384") {
		return std::make_unique < CryptoInterface::Sha3 > (384);
	} else if (name == "SHA3-512") {
		return std::make_unique < CryptoInterface::Sha3 > (512);
	} else if (HashUtility::isWhirlpool(name)) {
		//Whirlpool needs special handling, due to problems with the factory pattern
		std::cout << HashUtility::extractWhirlRounds(name) << std::endl;
		return std::make_unique < CryptoInterface::Whirlpool
				> (HashUtility::extractWhirlRounds(name));
	} else {
		throw std::invalid_argument("Hashfunction: " + name + " not found");
	}
}
;

} /* namespace CryptoInterface */
