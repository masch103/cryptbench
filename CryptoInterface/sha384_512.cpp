#include "hash_utility.h"
#include "sha384_512.h"
#include "stream_reader.h"
#include <cstring>
#include <iostream>
#include "file_not_found_exception.h"

namespace CryptoInterface {

Sha384_512::Sha384_512(unsigned int digestSize) :
		DIGESTSIZE_BIT(digestSize) {
	initializeMdBuffer(digestSize);
}

void Sha384_512::initializeMdBuffer(unsigned int digestSize) {
	if (digestSize == 512) {
		mdBuffer.A = 0x6a09e667f3bcc908;
		mdBuffer.B = 0xbb67ae8584caa73b;
		mdBuffer.C = 0x3c6ef372fe94f82b;
		mdBuffer.D = 0xa54ff53a5f1d36f1;
		mdBuffer.E = 0x510e527fade682d1;
		mdBuffer.F = 0x9b05688c2b3e6c1f;
		mdBuffer.G = 0x1f83d9abfb41bd6b;
		mdBuffer.H = 0x5be0cd19137e2179;
	} else if (digestSize == 384) {
		mdBuffer.A = 0xcbbb9d5dc1059ed8;
		mdBuffer.B = 0x629a292a367cd507;
		mdBuffer.C = 0x9159015a3070dd17;
		mdBuffer.D = 0x152fecd8f70e5939;
		mdBuffer.E = 0x67332667ffc00b31;
		mdBuffer.F = 0x8eb44a8768581511;
		mdBuffer.G = 0xdb0c2e0d64f98fa7;
		mdBuffer.H = 0x47b5481dbefa4fa4;
	} else {
		std::cout << "unvalid digest-size\n";
	}
}

std::string Sha384_512::getMessageDigest(const std::string& message,
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

std::string Sha384_512::computeMessageDigest(std::istream& inputStream) {
	unsigned char buffer[128];
	unsigned int bufferCount = 0;
	unsigned int mdBufferSize = DIGESTSIZE_BIT / 64;

	DoubleWord len64[2] = { 0, 0 };
	len64[0] = 0;
	len64[1] = 0;

	StreamReader streamReader { inputStream };

	//read as long as chars are in input stream
	while (!streamReader.read(buffer, 128)) {
		compress(buffer);
		HashUtility::addOnQuadWord(len64, BLOCKSIZE_BIT);
	}

	bufferCount = streamReader.getLastReadSize();
	HashUtility::addOnQuadWord(len64, bufferCount * 8);

	if (bufferCount == 128) {
		compress(buffer);
		bufferCount = 0;
	}

	DoubleWordSize padding_length =
			(bufferCount < 112) ? (112 - bufferCount) : (240 - bufferCount);

	buffer[bufferCount++] = static_cast<unsigned char> ( 0x80);
	for (unsigned int i = 0; i < padding_length - 1; i++) {
		if (bufferCount == 128) {
			//should only be triggered once
			compress(buffer);
			bufferCount = 0;
		}
		buffer[bufferCount++] = static_cast<unsigned char> (0x00);
	}

	//now we need to append the original_messageSize
	appendLength(buffer, len64, &bufferCount);

	//check if buffer size is exactly 128 bytes
	if (bufferCount != 128) {
		return std::string("FAILURE: BUFFERSize IS WRONG!");
	}

	compress(buffer);

	//build the hashvalue
	DoubleWord currentHashState[8] = { mdBuffer.A, mdBuffer.B, mdBuffer.C,
			mdBuffer.D, mdBuffer.E, mdBuffer.F, mdBuffer.G, mdBuffer.H };

	std::string stringDigest { };

	//cut the digest depending on the desired algorithm(that is SHA-384 or SHA-512)
	for (unsigned int i = 0; i < mdBufferSize; i++) {
		std::string test = HashUtility::intToHexString(currentHashState[i], 16);
		stringDigest.append(test);
	}

	return stringDigest;
}

void Sha384_512::compress(const unsigned char block[128]) {
	DoubleWord A = mdBuffer.A, B = mdBuffer.B, C = mdBuffer.C, D = mdBuffer.D,
			E = mdBuffer.E, F = mdBuffer.F, G = mdBuffer.G, H = mdBuffer.H;
	DoubleWord cache1, cache2, X[80];

	//fill the first 16 Words of the array with the Words from the original block
	decode(X, block, 128);

	//expand the 16 Words to 80
	for (unsigned int j = 16; j < 80; j++) {
		X[j] = sigmaOne(X[j - 2]) + X[j - 7] + sigmaZero(X[j - 15]) + X[j - 16];
	}

	for (unsigned int i = 0; i < 80; i++) {
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
void Sha384_512::decode(DoubleWord X[], const unsigned char block[],
		WordSize blockLength) {
	for (unsigned int i = 0, j = 0; j < blockLength; i++, j += 8) {
		X[i] = (((DoubleWord) block[j]) << 56)
				| ((static_cast<DoubleWord> (block[j + 1])) << 48)
				| ((static_cast<DoubleWord> (block[j + 2])) << 40)
				| ((static_cast<DoubleWord> (block[j + 3])) << 32)
				| ((static_cast<DoubleWord> (block[j + 4])) << 24)
				| ((static_cast<DoubleWord> (block[j + 5])) << 16)
				| ((static_cast<DoubleWord> (block[j + 6])) << 8)
				| ((static_cast<DoubleWord> (block[j + 7])));
	}
}

/*
 * This code was derived from IETF RFC 6234.
 * Please reproduce this note if possible.
 */
void Sha384_512::appendLength(unsigned char* buffer, DoubleWord size[2],
		unsigned int* bufferCount) {
	for (int i = 1; i >= 0; i--) {
		buffer[(*bufferCount)++] = ((size[i] >> 56));
		buffer[(*bufferCount)++] = ((size[i] >> 48));
		buffer[(*bufferCount)++] = ((size[i] >> 40));
		buffer[(*bufferCount)++] = ((size[i] >> 32));
		buffer[(*bufferCount)++] = ((size[i] >> 24));
		buffer[(*bufferCount)++] = ((size[i] >> 16));
		buffer[(*bufferCount)++] = ((size[i] >> 8));
		buffer[(*bufferCount)++] = ((size[i] >> 0));
	}
}

Sha384_512::~Sha384_512() {

}

} /* namespace Benchmark */
