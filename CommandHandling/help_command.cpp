#include "help_command.h"
#include <iostream>

namespace CommandHandling {

HelpCommand::HelpCommand() {}

void HelpCommand::execute() {
	printHelp();
}

void HelpCommand::printHelp() {
	std::cout
			<< "cryptbench [MODE] [FUNC] [MESSAGE] [MESSAGE IS FILE] [OUTPUTFILE]\n\n"
			<< "CryptBench has two different modes: The basic and the bench mode.\n\n"
			<< "In basic mode, the user has the possibility to hash a file or a string with one SINGLE hash function.\n"
			<< "The message digest is directly printed to the command line.\n"
			<< "The input is as follows: cryptbench basic -f function -m file path/string {-i}\n\n"
			<< "In bench mode, the user can compare different hash functions, and the output is printed into a file defined by the user.\n"
			<< "The input is as follows: cryptbench bench -f func1,func2,..,funcN -m file path/string {-i}  {-o file path/string} {-a accuracy}\n"
			<< "If the user wishes to hash a file, he has to add the option -i ATTENTION: If a hash function is named twice, the duplicate will be ignored!\n"
			<< "For a complete list of supported hash functions please refer to 'cryptbench list'\n\n";
}

HelpCommand::~HelpCommand() {}

} /* namespace CommandHandling */
