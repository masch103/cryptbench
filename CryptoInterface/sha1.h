#ifndef SHA1_H_
#define SHA1_H_

#include "hashfunction.h"
#include <cstdint>

namespace CryptoInterface {

using Word = std::uint32_t;
using WordSize = std::uint32_t;
using DoubleWord = std::uint64_t;


class Sha1: public HashFunction {
private:
	const unsigned int BLOCKSIZE_BIT = 512;
	const unsigned int BLOCKSIZE_BYTE = 64;
	const unsigned int DIGESTSIZE_BIT = 160;
	const unsigned int DIGESTSIZE_BYTE = 20;

	struct RoundConstants {
		const Word constantRound1 = 0x5a827999;
		const Word constantRound2 = 0x6ed9eba1;
		const Word constantRound3 = 0x8f1bbcdc;
		const Word constantRound4 = 0xca62c1d6;
	} roundConstans;

	//boolean functions operation on 32 Bit Words, see RFC 3174 for further information
	Word boolFuncF(Word x, Word y, Word z) {
		return (x & y) | (~x & z);
	}
	;
	Word boolFuncG(Word x, Word y, Word z) {
		return x ^ y ^ z;
	}
	;
	Word boolFuncH(Word x, Word y, Word z) {
		return (x & y) | (x & z) | (y & z);
	}
	;
	Word boolFuncI(Word x, Word y, Word z) {
		return x ^ y ^ z;
	}
	;

	//according to RFC 3174
	Word rotateLeft(Word x, int n) {
		return (x << n) | (x >> (32 - n));
	}

	struct hashStatus {
		Word A;
		Word B;
		Word C;
		Word D;
		Word E;
	} mdBuffer;

	void compress(const unsigned char block[64]);
	void decode(Word X[], const unsigned char block[], WordSize blockLength);
	void appendLength(unsigned char* buffer, Word* size,
			unsigned int* bufferCount);
	std::string computeMessageDigest(std::istream& inputStream);
	void initializeMdBuffer();

public:
	Sha1();
	std::string getMessageDigest(const std::string& message,
			bool messageIsFile) override;
	virtual ~Sha1();
};

} /* namespace CryptoInterface */

#endif /* SHA1_H_ */
