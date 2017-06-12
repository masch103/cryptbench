#include "bench_dao.h"
#include "bench_mark_management.h"
#include "benchmark_exception.h"


namespace Benchmark {

BenchmarkManagment::BenchmarkManagment(
		std::vector<std::string>& functionsToExecute,
		const std::string& message, const bool messageIsFile, const int accuracy,
		BenchDaoPtr benchDao) :
		benchmark_ { functionsToExecute, message, messageIsFile, accuracy }, benchDao_ {
				std::move(benchDao) } {
}

void BenchmarkManagment::createBenchmark() {
	try{
		benchmark_.executeBenchmark();
		benchDao_->writeBenchResult(benchmark_.getDataObjects());
	} catch(BenchmarkException& e) {
		throw std::invalid_argument(e.what());
	}
}

BenchmarkManagment::~BenchmarkManagment() {
}

} /* namespace Benchmark */
