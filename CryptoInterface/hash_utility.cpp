#include "hash_utility.h"
#include <regex>

#include <iostream>
namespace CryptoInterface {

HashUtility::HashUtility() {}

bool HashUtility::isWhirlpool(const std::string& name) {
	std::regex whirlpoolName{"Whirlpool"};
	if(std::regex_search(name,whirlpoolName)) {
		return true;
	}
	return false;
}

unsigned int HashUtility::extractWhirlRounds(const std::string& name) {
	std::regex roundNumberReg{R"(Whirlpool([\d]+))"};
	std::smatch resultMatch;
	//check for: Whirlpool9, Whirlpool15,...
	if(std::regex_match(name, resultMatch, roundNumberReg)) {
		if(resultMatch.size() == 2) {
			 std::ssub_match roundNumberMatch = resultMatch[1];
			 //std::cout << std::stoul(roundNumberMatch.str()) << std::endl;
			 return std::stoul(roundNumberMatch.str());
		}
	}
	//retun basic number of rounds, when no numbers are specified
	return 10;
}
HashUtility::~HashUtility() {}

} /* namespace CryptoInterface */
