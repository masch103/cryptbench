#ifndef COMMANDLINE_UTILITY_H_
#define COMMANDLINE_UTILITY_H_

#include <vector>
#include <string>

namespace CommandHandling {

class CommandLineUtility {
public:
	template<class T>
	static bool vectorContainsValue(T value, std::vector<T>& vector) {
		for(auto element : vector) {
				if(element == value){
					return true;
				}
			}
			return false;
	};
	static void splitStringOnToken(const std::string input, std::vector<std::string>& returnVector, const char token);
	CommandLineUtility();
	~CommandLineUtility();
};

} /* namespace CommandHandling */

#endif /* COMMANDLINE_UTILITY_H_ */
