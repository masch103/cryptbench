#include "whirlpool.h"

#include <fstream>
#include <cstring>
#include "file_not_found_exception.h"
#include "hash_utility.h"
#include "stream_reader.h"
#include <iostream>

namespace CryptoInterface {

Whirlpool::Whirlpool(unsigned int rounds) {
	rounds_ = rounds;
	std::memset(state_, 0, sizeof(state_));
}

std::string Whirlpool::getMessageDigest(const std::string& message,
		bool messageIsFile) {
	if (messageIsFile) {
		std::ifstream inputStream;
		inputStream.open(message, std::ifstream::in);
		if (!inputStream.is_open()) {
			throw DataAccessInterface::FileNotFoundException {
					"Can't open message file: " + message };
		}
		return computeMessageDigest(inputStream);
	} else {
		std::stringstream inputStream(message);
		return computeMessageDigest(inputStream);
	}
}

std::string Whirlpool::computeMessageDigest(std::istream& inputStream) {
	unsigned char buffer[64];
	unsigned int bufferCount = 0;

	DoubleWord len64[2];
	len64[0] = 0;
	len64[1] = 0;

	StreamReader streamReader { inputStream };

	while (!streamReader.read(buffer, 64)) {
		compress(buffer);
		HashUtility::addOnQuadWord(len64, WhirlConstants::BLOCKSIZE_BIT);
	}

	bufferCount = streamReader.getLastReadSize();
	HashUtility::addOnQuadWord(len64, bufferCount * 8);

	if (bufferCount == 64) {
		compress(buffer);
		bufferCount = 0;
	}

	DoubleWordSize paddingLength =
			(bufferCount < 32) ? (32 - bufferCount) : (96 - bufferCount);

	buffer[bufferCount++] = static_cast<unsigned char>(0x80);
	for (unsigned int i = 0; i < paddingLength - 1; i++) {
		if (bufferCount == 64) {
			//should only be triggered one time
			compress(buffer);
			bufferCount = 0;
		}
		buffer[bufferCount++] = static_cast<unsigned char>(0x00);
	}

	//fill missing length with zeros
	while (bufferCount < 56) {
		buffer[bufferCount++] = static_cast<unsigned char>(0x00);
	}
	if (bufferCount != 56) {
		return std::string("FAILURE: BUFFERSize IS WRONG! 1");
	}
	appendLength(buffer, len64, &bufferCount);

	//check if buffer size is exactly 64 bytes
	if (bufferCount != 64) {
		return std::string("FAILURE: BUFFERSize IS WRONG! 2");
	}

	compress(buffer);

	std::string stringDigest { };

	for (unsigned int i = 0; i < 8; i++) {
		std::string test = HashUtility::intToHexString(state_[i], 16);
		stringDigest.append(test);
	}
	std::memset(state_, 0, sizeof(state_));

	return stringDigest;
}

void Whirlpool::compress(const unsigned char bufferBlock[64]) {
	DoubleWord roundKey[8];
	DoubleWord innerState[8];
	DoubleWord intermediateKey[8];
	DoubleWord block[8];

	decode(block, bufferBlock, 64);

	//compute K[0]
	for (unsigned int i = 0; i < 8; i++) {
		roundKey[i] = state_[i];
		innerState[i] = block[i] ^ roundKey[i];
	}

	//main loop of transformation
	for (unsigned int r = 0; r < rounds_; r++) {
		//compute K[r]
		for (unsigned int i = 0; i < 8; i++) {
			intermediateKey[i] = 0;
			intermediateKey[i] ^= computeKey(roundKey, i);
		}

		//add intermediateKey to original one
		for (unsigned int i = 0; i < 8; i++) {
			roundKey[i] = intermediateKey[i];
		}

		//Theta
		//work around for assurance of the correct round constants in all rounds,
		//not sure if this is correct according to reference
		roundKey[0] ^= WhirlConstants::ROUNDCONSTANTS[(r + 1) % 10];

		for (unsigned int i = 0; i < 8; i++) {
			intermediateKey[i] = roundKey[i];
			intermediateKey[i] ^= computeKey(innerState, i);
		}

		for (unsigned int i = 0; i < 8; i++) {
			innerState[i] = intermediateKey[i];
		}
	}

	//add innerState to global one
	for (unsigned int i = 0; i < 8; i++) {
		//keep in mind: Miyaguchi-Preenel
		state_[i] ^= innerState[i] ^ block[i];
	}
}

void Whirlpool::decode(DoubleWord X[], const unsigned char block[],
		unsigned int blockLength) {
	for (unsigned int i = 0, j = 0; j < blockLength; i++, j += 8) {
		//keep in mind: this is a big-endian implementation
		X[i] = (((DoubleWord) block[j]) << 56)
				| ((static_cast<DoubleWord>(block[j + 1])) << 48)
				| ((static_cast<DoubleWord>(block[j + 2])) << 40)
				| ((static_cast<DoubleWord>(block[j + 3])) << 32)
				| ((static_cast<DoubleWord>(block[j + 4])) << 24)
				| ((static_cast<DoubleWord>(block[j + 5])) << 16)
				| ((static_cast<DoubleWord>(block[j + 6])) << 8)
				| ((static_cast<DoubleWord>(block[j + 7])));
	}
}

void Whirlpool::appendLength(unsigned char* buffer, DoubleWord size[2],
		unsigned int* bufferCount) {
	for (int i = 1; i >= 0; i--) {
		buffer[(*bufferCount)++] = ((size[i] >> 24));
		buffer[(*bufferCount)++] = ((size[i] >> 16));
		buffer[(*bufferCount)++] = ((size[i] >> 8));
		buffer[(*bufferCount)++] = ((size[i] >> 0));
	}
}

Whirlpool::~Whirlpool() {
	// TODO Auto-generated destructor stub
}

} /* namespace CommandHandling */
