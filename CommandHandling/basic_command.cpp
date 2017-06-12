#include "basic_command.h"
#include <getopt.h>
#include "hashfunction.h"
#include "hashfunction_factory.h"
#include <iostream>
#include <unistd.h>
#include "file_not_found_exception.h"

namespace CommandHandling {

using HashPointer = std::unique_ptr<CryptoInterface::HashFunction>;

BasicCommand::BasicCommand(int argumentNumber, char* options[]) {
	options = &options[1];
	//evaluate options
	char optionChar = 0;
	while ((optionChar = getopt(argumentNumber - 1, options, "+hif:m:")) != -1) {
		switch (optionChar) {
		case 'h':
			printHelp();
			throw std::invalid_argument("");
			break;
		case 'f':
			functionToExecute_ = std::string(optarg);
			break;
		case 'm':
			inputFilepath_ = std::string(optarg);
			break;
		case 'i':
			messageIsFile_ = true;
			break;
		case '?':
			//Throw Exception for defined program termination, getopt handles err out
			printHelp();
			throw std::invalid_argument("");
			break;
		}
	}
}

void BasicCommand::execute() {
	HashPointer hashPointer { };
	try {
		hashPointer = CryptoInterface::HashFunctionFactory::createHashfunction(
				functionToExecute_);
		std::string messageDigest { };
		messageDigest = hashPointer->getMessageDigest(inputFilepath_,
				messageIsFile_);
		std::cout << messageDigest << std::endl;
	} catch (std::invalid_argument& e) {
		throw std::invalid_argument(e.what());
	} catch (DataAccessInterface::FileNotFoundException& e) {
		std::cout << e.what() << std::endl;
	}
}

void BasicCommand::printHelp() {
	std::cout
			<< "In basic mode, the user has the possibility to hash a file or a string with one SINGLE hash function.\n"
			<< "The message digest is directly printed to the Command-Line.\n"
			<< "The input is as follows: cryptbench basic -f function -m filepath/string {-i}\n";
}

BasicCommand::~BasicCommand() {
}

} /* namespace CommandHandling */
