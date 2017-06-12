#ifndef CRYPTOINTERFACE_HASHFUNCTION_H_
#define CRYPTOINTERFACE_HASHFUNCTION_H_

#include <string>


namespace CryptoInterface {

class HashFunction {
//Interface for HashFunctions ensures that all derived HashFunctions implement getMessageDigest()
public:
	HashFunction();
	virtual std::string getMessageDigest(const std::string&, bool) = 0;
	virtual ~HashFunction();
};

} /* namespace CryptoInterface */

#endif /* CRYPTOINTERFACE_HASHFUNCTION_H_ */
