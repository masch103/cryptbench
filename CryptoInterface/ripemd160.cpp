#include "hash_utility.h"
#include "ripemd160.h"
#include "stream_reader.h"
#include <cstring>
#include "file_not_found_exception.h"

namespace CryptoInterface {

Ripemd160::Ripemd160() {
	initializeMdBuffer();
}

void Ripemd160::initializeMdBuffer() noexcept {
	mdBuffer.A = 0x67452301;
	mdBuffer.B = 0xefcdab89;
	mdBuffer.C = 0x98badcfe;
	mdBuffer.D = 0x10325476;
	mdBuffer.E = 0xc3d2e1f0;
}

std::string Ripemd160::getMessageDigest(const std::string& message,
		bool messageIsFile) {
	initializeMdBuffer();
	if (messageIsFile) {
		std::ifstream inputStream;
		inputStream.open(message, std::ifstream::in);
		if (!inputStream.is_open()) {
			throw DataAccessInterface::FileNotFoundException {
					"Can't open message file: " + message };
		}
		return (computeMessageDigest(inputStream));
	} else {
		std::stringstream inputStream(message);
		return (computeMessageDigest(inputStream));
	}
}

std::string Ripemd160::computeMessageDigest(std::istream& inputStream) {
	unsigned char digest[20];
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

	buffer[bufferCount++] = static_cast<unsigned char>(0x80);
	for (unsigned int i = 0; i < paddingLength - 1; i++) {
		if (bufferCount == 64) {
			//should only be triggered one time
			compress(buffer);
			bufferCount = 0;
		}
		buffer[bufferCount++] = static_cast<unsigned char>(0x00);
	}

	//now we need to append the original_message_size
	encode(originalMessageSize, converter.len32, 8);
	for (unsigned int i = 0; i < 8; i++) {
		buffer[bufferCount++] = originalMessageSize[i];
	}

	//appendLength(buffer, converter.len32, &bufferCount);
	compress(buffer);

	//build the hashvalue
	Word currentHashState[5] = { mdBuffer.A, mdBuffer.B, mdBuffer.C, mdBuffer.D,
			mdBuffer.E };
	encode(digest, currentHashState, 20);

	std::string stringDigest { };
	for (unsigned int i = 0; i < 20; i++) {
		//need to cast the current digest(unsigned char) to unsinged int
		//the reason is, that otherwise type deduction(auto) doesn't work as intended
		stringDigest.append(
				HashUtility::intToHexString(
						static_cast<unsigned int>(digest[i]), 2));
	}

	memset(digest, 0, sizeof(digest));
	return (stringDigest);

}

void Ripemd160::compress(const unsigned char block[64]) noexcept {
	Word AL = mdBuffer.A, BL = mdBuffer.B, CL = mdBuffer.C, DL = mdBuffer.D,
			EL = mdBuffer.E;
	Word AR = mdBuffer.A, BR = mdBuffer.B, CR = mdBuffer.C, DR = mdBuffer.D,
			ER = mdBuffer.E;

	Word cacheLeftLine, cacheRightLine, X[16];

	decode(X, block, 64);

	for (unsigned int i = 0; i < 80; i++) {
		if (0 <= i && i < 16) {
			cacheLeftLine = AL + boolFuncF(BL, CL, DL)
					+ X[positionArrayLeftLine_[i]]
					+ roundConstantsLeftLine_.roundOne;

			cacheRightLine = AR + boolFuncJ(BR, CR, DR)
					+ X[positionArrayRightLine_[i]]
					+ roundConstantsRightLine_.roundOne;
		} else if (i >= 16 && i < 32) {
			cacheLeftLine = AL + boolFuncG(BL, CL, DL)
					+ X[positionArrayLeftLine_[i]]
					+ roundConstantsLeftLine_.roundTwo;
			cacheRightLine = AR + boolFuncI(BR, CR, DR)
					+ X[positionArrayRightLine_[i]]
					+ roundConstantsRightLine_.roundTwo;
		} else if (i >= 32 && i < 48) {
			cacheLeftLine = AL + boolFuncH(BL, CL, DL)
					+ X[positionArrayLeftLine_[i]]
					+ roundConstantsLeftLine_.roundThree;
			cacheRightLine = AR + boolFuncH(BR, CR, DR)
					+ X[positionArrayRightLine_[i]]
					+ roundConstantsRightLine_.roundThree;
		} else if (i >= 48 && i < 64) {
			cacheLeftLine = AL + boolFuncI(BL, CL, DL)
					+ X[positionArrayLeftLine_[i]]
					+ roundConstantsLeftLine_.roundFour;
			cacheRightLine = AR + boolFuncG(BR, CR, DR)
					+ X[positionArrayRightLine_[i]]
					+ roundConstantsRightLine_.roundFour;
		} else if (i >= 64 && i < 80) {
			cacheLeftLine = AL + boolFuncJ(BL, CL, DL)
					+ X[positionArrayLeftLine_[i]]
					+ roundConstantsLeftLine_.roundFive;
			cacheRightLine = AR + boolFuncF(BR, CR, DR)
					+ X[positionArrayRightLine_[i]]
					+ roundConstantsRightLine_.roundFive;
		}
		//LeftLine
		AL = EL;
		EL = DL;
		DL = rotateLeft(CL, 10);
		CL = BL;
		//Note: AL is used here, because EL is overridden
		BL = rotateLeft(cacheLeftLine, rotationsArrayLeftLine_[i]) + AL;

		//RightLine
		AR = ER;
		ER = DR;
		DR = rotateLeft(CR, 10);
		CR = BR;
		//Note: AR is used here, because ER is overridden
		BR = rotateLeft(cacheRightLine, rotationsArrayRightLine_[i]) + AR;
	}

	Word tempCache = mdBuffer.B + CL + DR;
	mdBuffer.B = mdBuffer.C + DL + ER;
	mdBuffer.C = mdBuffer.D + EL + AR;
	mdBuffer.D = mdBuffer.E + AL + BR;
	mdBuffer.E = mdBuffer.A + BL + CR;
	mdBuffer.A = tempCache;

	//clear memory, to prevent sniffing of memory
	memset(X, 0, sizeof(X));

}

void Ripemd160::decode(Word X[], const unsigned char block[],
		WordSize blockLength) noexcept {
	for (unsigned int i = 0, j = 0; j < blockLength; i++, j += 4) {
		X[i] = (static_cast<Word>(block[j]))
				| ((static_cast<Word>(block[j + 1])) << 8)
				| ((static_cast<Word>(block[j + 2])) << 16)
				| ((static_cast<Word>(block[j + 3])) << 24);
	}
}

void Ripemd160::encode(unsigned char* digest, const Word* hashState,
		WordSize digestLength) noexcept {
	for (unsigned int i = 0, j = 0; j < digestLength; i++, j += 4) {
		digest[j] = static_cast<unsigned int>((hashState[i] & 0xff));
		digest[j + 1] = static_cast<unsigned int>(((hashState[i] >> 8) & 0xff));
		digest[j + 2] = static_cast<unsigned int>(((hashState[i] >> 16) & 0xff));
		digest[j + 3] = static_cast<unsigned int>(((hashState[i] >> 24) & 0xff));
	}

}

Ripemd160::~Ripemd160() {
}

} /* namespace CryptoInterface */
