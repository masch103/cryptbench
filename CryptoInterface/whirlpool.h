#ifndef WHIRLPOOL_H_
#define WHIRLPOOL_H_

#include "hashfunction.h"
#include "whirl_constants.h"



namespace CryptoInterface {
/*
 * This class is implemented according to the java reference implementation
 * See thesis for more information and the link to the file
 */
class Whirlpool : public HashFunction {
private:
	DoubleWord state_[8];
	unsigned int rounds_;
	void compress(const unsigned char bufferBlock[64]);
	std::string computeMessageDigest(std::istream& inputStream);
	DoubleWord computeKey(DoubleWord source[8], int position) {
		DoubleWord intermidiate = WhirlConstants::SBOX0[static_cast<int>(source[(position - 0) & 7] >> 56)] ;
		intermidiate ^= WhirlConstants::SBOX1[static_cast<int>(source[(position - 1) & 7] >> 48) & 0xFF];
		intermidiate ^= WhirlConstants::SBOX2[static_cast<int>(source[(position - 2) & 7] >> 40) & 0xFF];
		intermidiate ^= WhirlConstants::SBOX3[static_cast<int>(source[(position - 3) & 7] >> 32) & 0xFF];
		intermidiate ^= WhirlConstants::SBOX4[static_cast<int>(source[(position - 4) & 7] >> 24) & 0xFF];
		intermidiate ^= WhirlConstants::SBOX5[static_cast<int>(source[(position - 5) & 7] >> 16) & 0xFF];
		intermidiate ^= WhirlConstants::SBOX6[static_cast<int>(source[(position - 6) & 7] >> 8) & 0xFF];
		intermidiate ^= WhirlConstants::SBOX7[static_cast<int>(source[(position - 7) & 7] >> 0) & 0xFF];

		return intermidiate;
	}
	void decode(DoubleWord X[], const unsigned char block[],
			unsigned int blockLength);
	void appendLength(unsigned char* buffer, DoubleWord size[2],
			unsigned int* bufferCount);
public:
	Whirlpool(unsigned int rounds = 10);
	std::string getMessageDigest(const std::string& message,
				bool messageIsFile);
	virtual ~Whirlpool();
};

} /* namespace CommandHandling */

#endif /* WHIRLPOOL_H_ */
