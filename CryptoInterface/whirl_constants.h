#ifndef WHIRL_CONSTANTS_H_
#define WHIRL_CONSTANTS_H_

#include <array>
#include <cstdint>

namespace CryptoInterface {

using Word = std::uint32_t;
using DoubleWord = std::uint64_t;
using DoubleWordSize = std::uint64_t;

class WhirlConstants {
public:
	static const unsigned int BLOCKSIZE_BIT = 512;
	static const unsigned int BLOCKSIZE_BYTE = BLOCKSIZE_BIT / 8;
	static const unsigned int DIGESTSIZE_BIT = 512;
	static const unsigned int DIGESTSIZE_BYTE = DIGESTSIZE_BIT / 8;
	static const unsigned int ROUNDS = 10;
	static const std::array<DoubleWord, (ROUNDS + 1)> ROUNDCONSTANTS;

	static const std::array<DoubleWord, 256> SBOX0;

	static const std::array<DoubleWord, 256> SBOX1;

	static const std::array<DoubleWord, 256> SBOX2;

	static const std::array<DoubleWord, 256> SBOX3;

	static const std::array<DoubleWord, 256> SBOX4;
	static const std::array<DoubleWord, 256> SBOX5;

	static const std::array<DoubleWord, 256> SBOX6;

	static const std::array<DoubleWord, 256> SBOX7;

	WhirlConstants();
	virtual ~WhirlConstants();
};

} /* namespace CommandHandling */

#endif /* WHIRL_CONSTANTS_H_ */
