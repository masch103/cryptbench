#include "command_engine.h"
#include "help_command.h"
#include "list_command.h"
#include "basic_command.h"
#include "bench_command.h"
#include <iostream>

#include <memory>

namespace CommandHandling {

using CommandPointer = std::unique_ptr<Command>;

CommandEngine::CommandEngine(int argc, char** argv) :
		argv_(argv) {
	argc_ = argc;
}

void CommandEngine::run() {
	CommandPointer commandPtr{};
	if(argv_[1] != nullptr) {
		std::string commandName { argv_[1] };
		try {
			if (commandName == "basic") {
				commandPtr = std::make_unique < BasicCommand > (argc_, argv_);
			} else if (commandName == "bench") {
				commandPtr = std::make_unique < BenchCommand > (argc_, argv_);
			} else if (commandName == "help") {
				commandPtr = std::make_unique<HelpCommand>();
			} else if (commandName == "list") {
				commandPtr = std::make_unique<ListCommand>();
			} else {
				std::cout << "Wrong agrument: " << commandName
						<< "\nSee 'cryptbench help' for more information\n";
			}
			if(commandPtr != nullptr) {
				commandPtr->execute();
			}
		} catch (std::invalid_argument& e) {
			std::cout << e.what() << "\nSee 'cryptbench help' for more information\n";

		}
	} else {
		std::cout << "No argument passed. See 'cryptbench help' for more information\n";
	}
}

CommandEngine::~CommandEngine() {
}

} /* namespace CommandHandling */
