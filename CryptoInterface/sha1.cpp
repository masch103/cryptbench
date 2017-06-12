#include "hash_utility.h"
#include "sha1.h"
#include "stream_reader.h"
#include <cstring>
#include "file_not_found_exception.h"

namespace CryptoInterface {

Sha1::Sha1() {
	initializeMdBuffer();
}

void Sha1::initializeMdBuffer() {
	mdBuffer.A = 0x67452301;
	mdBuffer.B = 0xefcdab89;
	mdBuffer.C = 0x98badcfe;
	mdBuffer.D = 0x10325476;
	mdBuffer.E = 0xc3d2e1f0;
}

std::string Sha1::getMessageDigest(const std::string& message,
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

std::string Sha1::computeMessageDigest(std::istream& inputStream) {
	unsigned char digest[20];
	unsigned char buffer[64];
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
	appendLength(buffer, converter.len32, &bufferCount);

	compress(buffer);

	//build the hashvalue
	Word currentHashState[5] = { mdBuffer.A, mdBuffer.B, mdBuffer.C, mdBuffer.D,
			mdBuffer.E };

	std::string stringDigest { };

	for (unsigned int i = 0; i < 5; i++) {
		std::string test = HashUtility::intToHexString(currentHashState[i], 8);
		stringDigest.append(test);
	}

	memset(digest, 0, sizeof(digest));
	return stringDigest;
}

void Sha1::compress(const unsigned char block[64]) {
	//basic compression function of SHA-1, see RFC 6234 for more information
	Word A = mdBuffer.A, B = mdBuffer.B, C = mdBuffer.C, D = mdBuffer.D, E =
			mdBuffer.E;
	Word cache, X[80];

	//fill the first 16 words of the array with the words from the original block
	decode(X, block, 64);

	//expand the 16 words to 80
	for (unsigned int j = 16; j < 80; j++) {
		X[j] = rotateLeft((X[j - 3] ^ X[j - 8] ^ X[j - 14] ^ X[j - 16]), 1);
	}

	for (unsigned int i = 0; i < 80; i++) {
		//Round 1
		if (i <= 19) {
			cache = rotateLeft(A, 5) + boolFuncF(B, C, D) + E + X[i]
					+ roundConstans.constantRound1;
		} else if (i >= 20 && i <= 39) {
			cache = rotateLeft(A, 5) + boolFuncG(B, C, D) + E + X[i]
					+ roundConstans.constantRound2;
		} else if (i >= 40 && i <= 59) {
			cache = rotateLeft(A, 5) + boolFuncH(B, C, D) + E + X[i]
					+ roundConstans.constantRound3;
		} else if (i >= 59 && i <= 79) {
			cache = rotateLeft(A, 5) + boolFuncI(B, C, D) + E + X[i]
					+ roundConstans.constantRound4;
		}
		E = D;
		D = C;
		C = rotateLeft(B, 30);
		B = A;
		A = cache;
	}

	mdBuffer.A += A;
	mdBuffer.B += B;
	mdBuffer.C += C;
	mdBuffer.D += D;
	mdBuffer.E += E;

	//clear memory, to prevent sniffing of memory
	memset(X, 0, sizeof(X));
}

/*
 * taken (and slightly customized) from RFC 6234
 */
void Sha1::decode(Word X[], const unsigned char block[], WordSize blockLength) {
	for (unsigned int i = 0, j = 0; j < blockLength; i++, j += 4) {
		X[i] = (static_cast<Word> (block[j]) & 0xff) << 24
				| ((static_cast<Word> (block[j + 1]) & 0xff) << 16)
				| ((static_cast<Word> (block[j + 2]) & 0xff) << 8)
				| ((static_cast<Word> (block[j + 3]) & 0xff));
	}
}

/*
 * taken (and slightly customized) from RFC 6234
 */
void Sha1::appendLength(unsigned char* buffer, Word size[2],
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

Sha1::~Sha1() {
	// TODO Auto-generated destructor stub
}

} /* namespace CryptoInterface */
