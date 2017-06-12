#include "hash_utility.h"
#include "md5.h"
#include "stream_reader.h"
#include <cstring>
#include "file_not_found_exception.h"

namespace CryptoInterface {

MessageDigest5::MessageDigest5() {
	initializeMdBuffer();
}

void MessageDigest5::initializeMdBuffer() noexcept {
	//initialize MDBuffer according to RFC 1321
	mdBuffer.A = 0x67452301;
	mdBuffer.B = 0xefcdab89;
	mdBuffer.C = 0x98badcfe;
	mdBuffer.D = 0x10325476;
}

//this function is highly redundant, but this is accepted in order to keep the interface (superclass) clean
std::string MessageDigest5::getMessageDigest(const std::string& message,
		bool messageIsFile) {
	initializeMdBuffer();
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

std::string MessageDigest5::computeMessageDigest(std::istream& inputStream) {
	unsigned char digest[16];
	unsigned char buffer[64];
	unsigned char originalMessageSize[8];
	unsigned int bufferCount = 0;

	StreamReader streamReader { inputStream };

	//needed to convert the message_length in two 32 Bit Words(little-endian)
	union convert64To32 {
		Word len32[2];
		std::uint64_t len64;
	} converter;

	converter.len64 = 0;

	//read as long as chars are in input stream
	while (!streamReader.read(buffer, 64)) {
		compress(buffer);
		converter.len64 += BLOCKSIZE_BIT;
	}

	bufferCount = streamReader.getLastReadSize();
	converter.len64 += bufferCount * 8;

	if (bufferCount == 64) {
		compress(buffer);
		bufferCount = 0;
	}

	WordSize paddingLength =
			(bufferCount < 56) ? (56 - bufferCount) : (120 - bufferCount);

	buffer[bufferCount++] = static_cast<unsigned char> ( 0x80);
	for (unsigned int i = 0; i < paddingLength - 1; i++) {
		if (bufferCount == 64) {
			//should only be triggered one time
			compress(buffer);
			bufferCount = 0;
		}
		buffer[bufferCount++] = static_cast<unsigned char> (0x00);
	}

	//now we need to append the original_message_size
	encode(originalMessageSize, converter.len32, 8);
	for (unsigned int i = 0; i < 8; i++) {
		buffer[bufferCount++] = originalMessageSize[i];
	}

	compress(buffer);

	//build the hashvalue
	Word currentHashState[4] =
			{ mdBuffer.A, mdBuffer.B, mdBuffer.C, mdBuffer.D };
	encode(digest, currentHashState, 16);

	std::string stringDigest { };
	for (unsigned int i = 0; i < 16; i++) {
		//need to cast the current digest(unsigned char) to unsinged int
		//the reason is, that otherwise type deduction(auto) doesn't work as intended
		stringDigest.append(
				HashUtility::intToHexString(static_cast<unsigned int> (digest[i]), 2));
	}

	memset(digest, 0, sizeof(digest));
	return stringDigest;

}

void MessageDigest5::compress(const unsigned char block[64]) noexcept {
	Word A = mdBuffer.A, B = mdBuffer.B, C = mdBuffer.C, D = mdBuffer.D;
	Word cache, X[16];

	decode(X, block, 64);

	for (unsigned int i = 0; i < 64; i++) {
		if (i <= 15) {
		 cache = A + boolFuncF(B, C, D) + sineConstants_[i]
		 + X[positionArray_[i]];
		 } else if (i >= 16 && i <= 31) {
		 cache = A + boolFuncG(B, C, D) + sineConstants_[i]
		 + X[positionArray_[i]];
		 } else if (i >= 32 && i <= 47) {
		 cache = A + boolFuncH(B, C, D) + sineConstants_[i]
		 + X[positionArray_[i]];
		 } else if (i >= 48 && i <= 63) {
		 cache = A + boolFuncI(B, C, D) + sineConstants_[i]
		 + X[positionArray_[i]];
		 }
		A = D;
		D = C;
		C = B;
		B = B + rotateLeft(cache, rotationsArray_[i]);

	}

	mdBuffer.A += A;
	mdBuffer.B += B;
	mdBuffer.C += C;
	mdBuffer.D += D;

	//clear memory, to prevent sniffing of memory
	memset(X, 0, sizeof(X));

}

/*
 * This code was derived from IETF RFC 1321.
 * Please reproduce this note if possible.
 */
void MessageDigest5::decode(Word X[], const unsigned char block[],
		WordSize blockLength) noexcept {
	for (unsigned int i = 0, j = 0; j < blockLength; i++, j += 4) {
		X[i] = (static_cast<Word> (block[j])) | ((static_cast<Word> (block[j + 1])) << 8)
				| ((static_cast<Word> (block[j + 2])) << 16) | ((static_cast<Word> (block[j + 3])) << 24);
	}
}

/*
 * This code was derived from IETF RFC 1321.
 * Please reproduce this note if possible.
 */
void MessageDigest5::encode(unsigned char* digest, const Word* hashState,
		WordSize digestLength) noexcept {
	for (unsigned int i = 0, j = 0; j < digestLength; i++, j += 4) {
		digest[j] = static_cast<unsigned int>( (hashState[i] & 0xff));
		digest[j + 1] = static_cast<unsigned int>(((hashState[i] >> 8) & 0xff));
		digest[j + 2] = static_cast<unsigned int>(((hashState[i] >> 16) & 0xff));
		digest[j + 3] = static_cast<unsigned int>(((hashState[i] >> 24) & 0xff));
	}
}

MessageDigest5::~MessageDigest5() {
}

} /* namespace CryptoInterface */
