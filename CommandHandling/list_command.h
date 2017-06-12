#ifndef COMMANDHANDLING_LIST_COMMAND_H_
#define COMMANDHANDLING_LIST_COMMAND_H_

#include "command.h"

namespace CommandHandling {

class ListCommand : public Command {
public:
	void execute() override;
	void printHelp() override;
	ListCommand();
	~ListCommand();
};

} /* namespace CommandHandling */

#endif /* COMMANDHANDLING_LIST_COMMAND_H_ */
