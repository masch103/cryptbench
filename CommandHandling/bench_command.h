#ifndef COMMANDHANDLING_BENCH_COMMAND_H_
#define COMMANDHANDLING_BENCH_COMMAND_H_

#include "command.h"
#include <string>
#include <vector>

namespace CommandHandling {

class BenchCommand: public Command {
private:
	int accuracy_ = 3;
	std::string message_;
	bool messageIsFile_ = false;
	std::string inputFilepath_;
	std::string outputFilepath_;
	std::vector<std::string> functionsToExecute_;
public:
	BenchCommand(int argumentNumber, char** options);
	void execute() override;
	void printHelp() override;
	~BenchCommand();
};

} /* namespace CommandHandling */

#endif /* COMMANDHANDLING_BENCH_COMMAND_H_ */
