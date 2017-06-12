#include "terminal_bench_dao.h"
#include <iostream>

namespace DataAccessInterface {

TerminalBenchDao::TerminalBenchDao() {}

void TerminalBenchDao::writeBenchResult(std::vector<Benchmark::DataObject<std::string>>& dataObjects) {
	for (auto& dataObject : dataObjects) {
		std::cout << dataObject;
	}
	std::cout << "------------------------------\n";
}

TerminalBenchDao::~TerminalBenchDao() {}

} /* namespace DataAccessInterface */
