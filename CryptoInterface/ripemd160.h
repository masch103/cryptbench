#ifndef RIPEMD160_H_
#define RIPEMD160_H_

#include "hashfunction.h"
#include <array>
#include <cstdint>

namespace CryptoInterface {

//unit32_t is used to ensure 32 Bit integer on all platforms (for x86_64 in particular)
using Word = std::uint32_t;
using WordSize = std::uint32_t;
using DoubleWord = std::uint64_t;

class Ripemd160 : public HashFunction{

private:
	static const unsigned int BLOCKSIZE_BIT = 512;
	static const unsigned int BLOCKSIZE_BYTE = 64;

	std::array<Word, 80> rotationsArrayLeftLine_ { { 11, 14, 15, 12, 5, 8, 7, 9,
			11, 13, 14, 15, 6, 7, 9, 8, 7, 6, 8, 13, 11, 9, 7, 15, 7, 12, 15, 9,
			11, 7, 13, 12, 11, 13, 6, 7, 14, 9, 13, 15, 14, 8, 13, 6, 5, 12, 7,
			5, 11, 12, 14, 15, 14, 15, 9, 8, 9, 14, 5, 6, 8, 6, 5, 12, 9, 15, 5,
			11, 6, 8, 13, 12, 5, 12, 13, 14, 11, 8, 5, 6 } };

	std::array<Word, 80> rotationsArrayRightLine_ { { 8, 9, 9, 11, 13, 15, 15,
			5, 7, 7, 8, 11, 14, 14, 12, 6, 9, 13, 15, 7, 12, 8, 9, 11, 7, 7, 12,
			7, 6, 15, 13, 11, 9, 7, 15, 11, 8, 6, 6, 14, 12, 13, 5, 14, 13, 13,
			7, 5, 15, 5, 8, 11, 14, 14, 6, 14, 6, 9, 12, 9, 12, 5, 15, 8, 8, 5,
			12, 9, 12, 5, 14, 6, 8, 13, 6, 5, 15, 13, 11, 11 } };

	std::array<Word, 80> positionArrayLeftLine_ { { 0, 1, 2, 3, 4, 5, 6, 7, 8,
			9, 10, 11, 12, 13, 14, 15, 7, 4, 13, 1, 10, 6, 15, 3, 12, 0, 9, 5,
			2, 14, 11, 8, 3, 10, 14, 4, 9, 15, 8, 1, 2, 7, 0, 6, 13, 11, 5, 12,
			1, 9, 11, 10, 0, 8, 12, 4, 13, 3, 7, 15, 14, 5, 6, 2, 4, 0, 5, 9, 7,
			12, 2, 10, 14, 1, 3, 8, 11, 6, 15, 13 } };

	std::array<Word, 80> positionArrayRightLine_ { { 5, 14, 7, 0, 9, 2, 11, 4,
			13, 6, 15, 8, 1, 10, 3, 12, 6, 11, 3, 7, 0, 13, 5, 10, 14, 15, 8,
			12, 4, 9, 1, 2, 15, 5, 1, 3, 7, 14, 6, 9, 11, 8, 12, 2, 10, 0, 4,
			13, 8, 6, 4, 1, 3, 11, 15, 0, 5, 12, 2, 13, 9, 7, 10, 14, 12, 15,
			10, 4, 1, 5, 8, 7, 6, 2, 13, 14, 0, 3, 9, 11 } };

	struct RoundConstants {
		Word roundOne;
		Word roundTwo;
		Word roundThree;
		Word roundFour;
		Word roundFive;
	};

	RoundConstants roundConstantsLeftLine_ { 0x00000000, 0x5a827999, 0x6ed9eba1,
			0x8f1bbcdc, 0xa953fd4e };
	RoundConstants roundConstantsRightLine_ { 0x50a28be6, 0x5c4dd124,
			0x6d703ef3, 0x7a6d76e9, 0x00000000 };

	//always inline!
	Word boolFuncF(Word x, Word y, Word z) {
		return x ^ y ^ z;
	}
	;
	Word boolFuncG(Word x, Word y, Word z) {
		return (x & y) | (~x & z);
	}
	;
	Word boolFuncH(Word x, Word y, Word z) {
		return (x | ~y) ^ z;
	}
	;
	Word boolFuncI(Word x, Word y, Word z) {
		return (x & z) | (y & ~z);
	}
	;
	Word boolFuncJ(Word x, Word y, Word z) {
		return x ^ (y | ~z);
	}
	;

	Word rotateLeft(Word x, int n) {
		return (x << n) | (x >> (32 - n));
	}

	//should be hold in register, but keyword 'register' is deprecated since C++11, which is used here
	struct HashStatus {
		Word A;
		Word B;
		Word C;
		Word D;
		Word E;
	} mdBuffer;

	void compress(const unsigned char block[64]) noexcept;
	void decode(Word X[], const unsigned char block[], WordSize blockLength)
			noexcept;
	void encode(unsigned char* digest, const Word* mdBuffer,
			WordSize digestLength) noexcept;
	std::string computeMessageDigest(std::istream& inputStream);
	void initializeMdBuffer() noexcept;
public:
	Ripemd160();
	std::string getMessageDigest(const std::string& message, bool messageIsFile) override;
	virtual ~Ripemd160();
};

} /* namespace CryptoInterface */

#endif /* RIPEMD160_H_ */
