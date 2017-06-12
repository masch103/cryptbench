#include "hash_utility.h"
#include "sha3.h"
#include "stream_reader.h"
#include <cstring>
#include "file_not_found_exception.h"

namespace CryptoInterface {

Sha3::Sha3(unsigned int digestSize) {
	digestSize_ = digestSize;
	capacity_ = digestSize_ << 1;
	rate_ = 1600 - capacity_;
	std::memset(state_, 0, 200);
}

std::string Sha3::getMessageDigest(const std::string& message,
		bool messageIsFile) {
	std::memset(state_, 0, 200);
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

std::string Sha3::computeMessageDigest(std::istream& inputStream) {
	//start with absorbing phase
	unsigned int bufferCount = 0;
	unsigned int rateInByte = rate_ / 8;
	unsigned char buffer[rateInByte];
	std::memset(buffer, 0, rateInByte);
	StreamReader streamReader { inputStream };

	//absorb while there are enough message blocks that fits the rate; doesen't affect bufferCount
	while (!streamReader.read(buffer, rateInByte)) {
		//Need to xor the buffer to the state
		for (unsigned int i = 0; i < rateInByte; i++) {
			state_[i] ^= buffer[i];
		}
		compress();
	}

	//Start padding
	bufferCount = streamReader.getLastReadSize();

	//Need to flush the buffer, since we do not copy it directly into the state
	if ((bufferCount % rateInByte) != 0) {
		for (unsigned int i = 0; i < bufferCount; i++) {
			state_[i] ^= buffer[i];
		}
	}

	//TODO: necessary?
	if (bufferCount == rateInByte) {
		compress();
		bufferCount = 0;
	}

	//Need at least two bytes to execute pad10*1
	state_[bufferCount++] ^= MAGICBYTE;
	if (bufferCount == rateInByte) {
		for (unsigned int i = 0; i < rateInByte; i++) {
			state_[i] ^= buffer[i];
		}
		compress();
		bufferCount = 0;
	}

	for (unsigned int i = bufferCount; i < rateInByte - 1; i++) {
		state_[bufferCount++] ^= 0;
	}

	state_[bufferCount] ^= 0x80;

	compress();

	//Now we need to build the message digest
	std::string messageDigest("");
	unsigned int digestSizeInByte = digestSize_ / 8;

	do {
		unsigned char intermidiateState[digestSizeInByte];
		std::memcpy(intermidiateState, state_, digestSizeInByte);
		for (unsigned int i = 0; i < digestSizeInByte; i++) {
			std::string test = HashUtility::intToHexString(
					static_cast<unsigned int> (intermidiateState[i]), 2);
			messageDigest.append(test);
		}

		compress();
	} while (messageDigest.size() <= digestSizeInByte);

	return messageDigest;
}

void Sha3::compress() {
	for (unsigned int i = 0; i < ROUNDS; i++) {
		theta();
		rho();
		pi();
		chi();
		iota(i);
	}
}

void Sha3::theta() {
	//C and D are lanes
	unsigned int x, y;
	DoubleWord C[5], D[5];

	for (x = 0; x < 5; x++) {
		C[x] = 0;
		for (y = 0; y < 5; y++)
			C[x] ^= accessLane(x, y);
	}
	for (x = 0; x < 5; x++) {
		D[x] = rotateLeft(C[(x + 1) % 5], 1) ^ C[(x + 4) % 5];
	}
	for (x = 0; x < 5; x++)
		for (y = 0; y < 5; y++) {
			DoubleWord cache = accessLane(x, y) ^ D[x];
			writeLane(x, y, cache);
		}

}

void Sha3::rho() {
	int x = 1;
	int y = 0;
	for (int t = 0; t < 24; t++) {
		unsigned int offset = ((t + 1) * (t + 2) / 2) % W;
		writeLane(x, y, rotateLeft(accessLane(x, y), offset));
		unsigned int temp = x;
		x = y, y = (2 * temp + 3 * y) % 5;
	}
}

void Sha3::pi() {
	//very inefficient as we need too many iterations over 25
	//TODO: optimization
	DoubleWord laneCache[25];
	for (int x = 0; x < 5; x++) {
		for (int y = 0; y < 5; y++) {
			laneCache[x + 5 * y] = accessLane(x, y);
		}
	}
	for (int x = 0; x < 5; x++) {
		for (int y = 0; y < 5; y++) {
			DoubleWord cache = laneCache[x + 5 * y];
			int newX = y;
			int newY = (2 * x + 3 * y) % 5;
			writeLane(newX, newY, cache);
		}
	}

}

void Sha3::chi() {
	DoubleWord cache[5];
	for (int y = 0; y < 5; y++) {
		for (int x = 0; x < 5; x++) {
			//First we need to make copies of the values, or we will overwrite the
			//needed Lanes
			cache[x] = accessLane(x, y);
		}
		for (int x = 0; x < 5; x++) {
			writeLane(x, y,
					cache[x] ^ ((~cache[(x + 1) % 5]) & cache[(x + 2) % 5]));
		}
	}
}

void Sha3::iota(unsigned int roundNumber) {
	DoubleWord cache = accessLane(0, 0) ^ ROUNDCONSTANTS[roundNumber];
	writeLane(0, 0, cache);
}

Sha3::~Sha3() {
}

} /* namespace StandaloneHashfunctions */
