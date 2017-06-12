#ifndef HASH_UTILITY_H_
#define HASH_UTILITY_H_

#include <cstdint>
#include <iomanip>
#include <sstream>

namespace CryptoInterface {

using StringStream = std::stringstream;

class HashUtility {
public:
	HashUtility();
	//since auto in function declaration is not allowed on every compiler, we use a template method instead
	template<class T>
	static std::string intToHexString(T i, short width){
		StringStream stringStream{};
		stringStream << std::hex << std::setfill('0') << std::setw(width) << i;
		return stringStream.str();
	}
	//TODO detect availability of 128 Bit words
	//see "https://gcc.gnu.org/onlinedocs/gcc/_005f_005fint128.html" for more information
	static void addOnQuadWord(std::uint64_t quadWord[2], std::uint64_t summand) {
		//detect overflow
		if((quadWord[0] + summand) <  quadWord[0] || (quadWord[0] + summand) < summand){
			//cut result to 64 bit word
			quadWord[0] = ((quadWord[0] + summand) & 0xFFFFFFFFFFFFFFFF);
			quadWord[1]++;
		}else {
			quadWord[0] += summand;
		}
	}
	static bool isWhirlpool(const std::string& name);
	static unsigned int extractWhirlRounds(const std::string& name);
	~HashUtility();
};

} /* namespace CryptoInterface */

#endif /* HASH_UTILITY_H_ */
