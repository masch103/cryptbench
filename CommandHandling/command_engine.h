#ifndef COMMANDHANDLING_COMMAND_ENGINE_H_
#define COMMANDHANDLING_COMMAND_ENGINE_H_

#include "command.h"

namespace CommandHandling {

class CommandEngine {
private:
	//Need to use C-Array
	int argc_;
	char** argv_;
public:
	CommandEngine(int argc, char* argv[]);
	void run();
	~CommandEngine();
};

} /* namespace CommandHandling */

#endif /* COMMANDHANDLING_COMMAND_ENGINE_H_ */
