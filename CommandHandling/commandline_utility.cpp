#include "commandline_utility.h"
#include <sstream>


namespace CommandHandling {

CommandLineUtility::CommandLineUtility() {}

void CommandLineUtility::splitStringOnToken(const std::string input, std::vector<std::string>& returnVector, const char token) {
	std::string stringBuffer;;
	std::stringstream inputStream{input};
	while(std::getline(inputStream, stringBuffer, token)){
		if(!vectorContainsValue(stringBuffer, returnVector)) {
			returnVector.push_back(stringBuffer);
		}
	}
}



CommandLineUtility::~CommandLineUtility() {}

} /* namespace CommandLineInterface */
