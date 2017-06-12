#ifndef COMMANDHANDLING_BASIC_COMMAND_H_
#define COMMANDHANDLING_BASIC_COMMAND_H_

#include "command.h"
#include <string>

namespace CommandHandling {

class BasicCommand: public Command {
private:
	std::string message_ ;
	std::string functionToExecute_ ;
	bool messageIsFile_ = false;
	std::string inputFilepath_ ;
public:
	BasicCommand(int argumentNumber, char* options[]);
	void execute() override;
	const std::string& getFunctionToExecute() const {
		return functionToExecute_;
	}
	;
	void printHelp() override;
	~BasicCommand();
};

} /* namespace CommandHandling */

#endif /* COMMANDHANDLING_BASIC_COMMAND_H_ */
