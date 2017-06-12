#ifndef SHA3_H_
#define SHA3_H_

#include "hashfunction.h"
#include <array>
#include <cstdint>

namespace CryptoInterface {

using Word = std::uint32_t;
using WordSize = std::uint32_t;
using DoubleWord = std::uint64_t;
using DoubleWordSize = std::uint64_t;

/*
 * This Class computes SHA-3 message digests. (That is SHA3-224/256/384/512)
 * Therefore only KECCAK-f[1600] is implemented, because no other parameters are required.
 * In case KECCAK-f[1600] is implemented, following parameters are fixed. (For more Information see Thesis)
 *
 * Length of State: 1600 bits
 * Number of Rounds: 24
 * Padding function: pad10*1
 * Padding byte: '0x06'
 * Expansion of State Array in z direction(w): 64
 *
 * The Capacity depends on the desired digest size.
 * SHA3-224: 448
 * SHA3-256: 512
 * SHA3-384: 768
 * SHA3-512: 1024
 */
class Sha3 : public HashFunction{
private:
	//Is only used for SHA-3
	unsigned char MAGICBYTE = 0x06;
	//KECCAK-f[1600] == KECCAK-p[1600,24]; 24 denotes the number of rounds
	const unsigned short ROUNDS = 24;
	const unsigned int W = 64;
	//The State of KECCAK-f[1600] consists of 1600 Bits == 200 Bytes
	unsigned char state_[200];
	unsigned int digestSize_;
	unsigned int capacity_;
	unsigned int rate_;

	const std::array<DoubleWord, 24> ROUNDCONSTANTS = { { 0x0000000000000001,
			0x0000000000008082, 0x800000000000808A, 0x8000000080008000,
			0x000000000000808B, 0x0000000080000001, 0x8000000080008081,
			0x8000000000008009, 0x000000000000008A, 0x0000000000000088,
			0x0000000080008009, 0x000000008000000A, 0x000000008000808B,
			0x800000000000008B, 0x8000000000008089, 0x8000000000008003,
			0x8000000000008002, 0x8000000000000080, 0x000000000000800A,
			0x800000008000000A, 0x8000000080008081, 0x8000000000008080,
			0x0000000080000001, 0x8000000080008008 } };

	const DoubleWord accessLane(unsigned int x, unsigned int y) {
		/*
		 union laneAccessor {
		 unsigned char laneInByte[8];
		 DoubleWord laneInDoubleWord;
		 } lane;
		 for (int i = 0; i < (W >> 3); i++) {
		 lane.laneInByte[i] = state[8 * (x + 5 * y) + i];
		 }
		 return lane.laneInDoubleWord;
		 */
		//taken from https://github.com/gvanas/KeccakCodePackage/blob/master/Standalone/CompactFIPS202/Keccak-readable-and-compact.c
		return reinterpret_cast<DoubleWord*>(state_)[x + 5 * y];
	}

	void writeLane(unsigned int x, unsigned int y, DoubleWord lane) {
		//taken from https://github.com/gvanas/KeccakCodePackage/blob/master/Standalone/CompactFIPS202/Keccak-readable-and-compact.c
		reinterpret_cast<DoubleWord*>(state_)[x + 5 * y] = lane;
	}

	DoubleWord rotateLeft(DoubleWord x, int n) {
		return (x << n) | (x >> (64 - n));
	}
	void compress();
	std::string computeMessageDigest(std::istream& inputStream);
	void theta();
	void rho();
	void pi();
	void chi();
	void iota(unsigned int roundNumber);
	void piRhoEfficient();
public:
	Sha3(unsigned int digestSize);
	std::string getMessageDigest(const std::string& message,
			bool messageIsFile) override;
	virtual ~Sha3();
};

} /* namespace StandaloneHashfunctions */

#endif /* SHA3_H_ */
