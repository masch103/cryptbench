#include "hash_utility.h"
#include "sha224_256.h"
#include "stream_reader.h"
#include <cstring>
#include <iostream>
#include "file_not_found_exception.h"

namespace CryptoInterface {

Sha224_256::Sha224_256(unsigned int digestSize) :
		DIGESTSIZE_BIT(digestSize) {
	initializeMdBuffer(digestSize);
}

void Sha224_256::initializeMdBuffer(unsigned int digestSize) {
	if (digestSize == 256) {
		mdBuffer.A = 0x6a09e667;
		mdBuffer.B = 0xbb67ae85;
		mdBuffer.C = 0x3c6ef372;
		mdBuffer.D = 0xa54ff53a;
		mdBuffer.E = 0x510e527f;
		mdBuffer.F = 0x9b05688c;
		mdBuffer.G = 0x1f83d9ab;
		mdBuffer.H = 0x5be0cd19;
	} else if (digestSize == 224) {
		mdBuffer.A = 0xc1059ed8;
		mdBuffer.B = 0x367cd507;
		mdBuffer.C = 0x3070dd17;
		mdBuffer.D = 0xf70e5939;
		mdBuffer.E = 0xffc00b31;
		mdBuffer.F = 0x68581511;
		mdBuffer.G = 0x64f98fa7;
		mdBuffer.H = 0xbefa4fa4;
	} else {
		std::cout << "unvalid digest-size\n";
	}
}

std::string Sha224_256::getMessageDigest(const std::string& message,
		bool messageIsFile) {
	initializeMdBuffer(DIGESTSIZE_BIT);
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

std::string Sha224_256::computeMessageDigest(std::istream& inputStream) {
	unsigned char buffer[64];
	unsigned int bufferCount = 0;
	unsigned int mdBufferSize = DIGESTSIZE_BIT / 32;

	StreamReader streamReader { inputStream };

	//needed to convert the message_length in two 32 Bit Words(little-endian)
	union convert64To32 {
		Word len32[2];
		std::uint64_t len64;
		unsigned char len8[8];
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

	//now we need to append the original_messageSize
	appendLength(buffer, converter.len32, &bufferCount);

	//check if buffer size is exactly 64 bytes
	if (bufferCount != 64) {
		return std::string("FAILURE: BUFFERSize IS WRONG!");
	}

	compress(buffer);

	//build the hashvalue
	Word currentHashState[8] = { mdBuffer.A, mdBuffer.B, mdBuffer.C, mdBuffer.D,
			mdBuffer.E, mdBuffer.F, mdBuffer.G, mdBuffer.H };

	std::string stringDigest { };

	//cut the digest depending on the desired algorithm(that is SHA-224 or SHA-256)
	for (unsigned int i = 0; i < mdBufferSize; i++) {
		std::string test = HashUtility::intToHexString(currentHashState[i], 8);
		stringDigest.append(test);
	}
	return stringDigest;
}

void Sha224_256::compress(const unsigned char block[64]) {
	Word A = mdBuffer.A, B = mdBuffer.B, C = mdBuffer.C, D = mdBuffer.D, E =
			mdBuffer.E, F = mdBuffer.F, G = mdBuffer.G, H = mdBuffer.H;
	Word cache1, cache2, X[64];

	//fill the first 16 Words of the array with the Words from the original block
	decode(X, block, 64);

	//expand the 16 Words to 80
	for (unsigned int j = 16; j < 64; j++) {
		X[j] = sigmaOne(X[j - 2]) + X[j - 7] + sigmaZero(X[j - 15]) + X[j - 16];
	}

	for (unsigned int i = 0; i < 64; i++) {
		cache1 = H + boolFuncI(E) + boolFuncF(E, F, G) + roundConstants_[i]
				+ X[i];
		cache2 = boolFuncG(A) + boolFuncH(A, B, C);
		H = G;
		G = F;
		F = E;
		E = D + cache1;
		D = C;
		C = B;
		B = A;
		A = cache1 + cache2;
	}

	mdBuffer.A += A;
	mdBuffer.B += B;
	mdBuffer.C += C;
	mdBuffer.D += D;
	mdBuffer.E += E;
	mdBuffer.F += F;
	mdBuffer.G += G;
	mdBuffer.H += H;

	//clear memory, to prevent sniffing of memory
	memset(X, 0, sizeof(X));
}

/*
 * This code was derived from IETF RFC 6234.
 * Please reproduce this note if possible.
 */
void Sha224_256::decode(Word X[], const unsigned char block[],
		WordSize blockLength) {
	for (unsigned int i = 0, j = 0; j < blockLength; i++, j += 4) {
			X[i] = (static_cast<Word> (block[j]) & 0xff) << 24
					| ((static_cast<Word> (block[j + 1]) & 0xff) << 16)
					| ((static_cast<Word> (block[j + 2]) & 0xff) << 8)
					| ((static_cast<Word> (block[j + 3]) & 0xff));
		}
}

/*
 * This code was derived from IETF RFC 6234.
 * Please reproduce this note if possible.
 */
void Sha224_256::appendLength(unsigned char* buffer, Word size[2],
		unsigned int* bufferCount) {
	buffer[(*bufferCount)++] = ((size[1] >> 24));
	buffer[(*bufferCount)++] = ((size[1] >> 16));
	buffer[(*bufferCount)++] = ((size[1] >> 8));
	buffer[(*bufferCount)++] = ((size[1] >> 0));
	buffer[(*bufferCount)++] = ((size[0] >> 24));
	buffer[(*bufferCount)++] = ((size[0] >> 16));
	buffer[(*bufferCount)++] = ((size[0] >> 8));
	buffer[(*bufferCount)++] = ((size[0] >> 0));
}

Sha224_256::~Sha224_256() {

}

} /* namespace Benchmark */
