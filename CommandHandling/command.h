#ifndef COMMANDHANDLING_COMMAND_H_
#define COMMANDHANDLING_COMMAND_H_


namespace CommandHandling {

class Command {
	/*
	 * This Class is meant to run the code of the crypto-API or benchmark-API, and return a hashvalue
	 */

public:
	Command();
	virtual ~Command();
	virtual void printHelp() = 0;
	virtual void execute() = 0;
};

} /* namespace CommandHandling */

#endif /* COMMANDHANDLING_COMMAND_H_ */
