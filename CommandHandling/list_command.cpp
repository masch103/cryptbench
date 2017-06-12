#include "list_command.h"
#include <iostream>
#include "hashfunction_factory.h"

namespace CommandHandling {

ListCommand::ListCommand() {
}

void ListCommand::execute() {
	std::cout << " Supported hash functions are:: \n";
	for (auto hashFunctionName : CryptoInterface::supportedHashfunctions) {
		std::cout << hashFunctionName << "\n";
	}
	std::cout << "For more Information see: 'cryptbench help'\n\n";
}

void ListCommand::printHelp() {

	std::cout << "This command lists all supported hash functions\n\n"
			<< "For more Information see: 'cryptbench help' \n\n";
}

ListCommand::~ListCommand() {
}

} /* namespace CommandHandling */
