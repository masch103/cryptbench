#ifndef COMMANDHANDLING_HELP_COMMAND_H_
#define COMMANDHANDLING_HELP_COMMAND_H_

#include "command.h"

namespace CommandHandling {

class HelpCommand : public Command {
public:
	HelpCommand();
	void execute() override;
	void printHelp() override;
	~HelpCommand();
};

} /* namespace CommandHandling */

#endif /* COMMANDHANDLING_HELP_COMMAND_H_ */
