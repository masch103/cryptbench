#include "bench_command.h"
#include "bench_mark_management.h"
#include "commandline_utility.h"
#include "file_bench_dao.h"
#include "terminal_bench_dao.h"
#include <getopt.h>
#include "file_not_found_exception.h"
#include <memory>
#include <stdlib.h>

namespace CommandHandling {

using FunctionVector = std::vector<std::string>;

BenchCommand::BenchCommand(int argumentNumber, char* options[]) {
	options = &options[1];
	//evaluate options
		char optionChar = 0;
			while ((optionChar = getopt(argumentNumber - 1, options, "hf:m:io:a:")) != -1) {
				switch (optionChar) {
				case 'h':
					printHelp();
					throw std::invalid_argument("");
					break;
				case 'f':
					CommandLineUtility::splitStringOnToken(std::string(optarg), functionsToExecute_,',');
					break;
				case 'm':
					inputFilepath_ = std::string(optarg);
					break;
				case 'i':
					messageIsFile_ = true;
					break;
				case 'o':
					outputFilepath_ = std::string(optarg);
					break;
				case 'a':
					accuracy_ = std::atoi(optarg);
					break;
				case '?':
					//Throw Exception for defined program termination, getopt handles err out
					printHelp();
					throw std::invalid_argument("");
					break;
				}
			}
}

BenchCommand::~BenchCommand() {}


void BenchCommand::execute(){
	std::unique_ptr<DataAccessInterface::BenchDao> benchDao;
	try{
		if(outputFilepath_ != "") {
			benchDao = std::make_unique<DataAccessInterface::FileBenchDao>(outputFilepath_);
		} else {
			benchDao = std::make_unique<DataAccessInterface::TerminalBenchDao>();
		}
		Benchmark::BenchmarkManagment benchmarkManagment{functionsToExecute_, inputFilepath_, messageIsFile_ , accuracy_, std::move(benchDao)};
		benchmarkManagment.createBenchmark();
	} catch(std::invalid_argument& e ){
		std::cout << e.what() << std::endl;
	} catch(DataAccessInterface::FileNotFoundException& e) {
		std:: cout << e.what() << std::endl;
	}
}

void BenchCommand::printHelp() {
	std::cout << "In bench mode, the user can compare different hash functions, and the output is printed into a file defined by the user.\n"
			<< "The input is as follows: cryptbench bench -f func1,func2,..,funcN -m file path/string {-i}  {-o file path/string} {-a accuracy}\n"
			<< "If the user wishes to hash a file, he has to add the option -i ATTENTION: If a hash function is named twice, the duplicate will be ignored!!\n"
			<< "The accuracy of the bench mark is determined by the accuracy value. The higher the accuracy the longer the runtime\n";
}

} /* namespace CommandHandling */
