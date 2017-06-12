#ifndef BENCHMARK_BENCH_MARK_MANAGEMENT_H_
#define BENCHMARK_BENCH_MARK_MANAGEMENT_H_


#include "bench_mark.h"
#include <vector>
#include <memory>

namespace DataAccessInterface {
class BenchDao;
} /* namespace DataAccessInterface */


namespace Benchmark {

using BenchDaoPtr = std::unique_ptr<DataAccessInterface::BenchDao>;

class BenchmarkManagment {
private:
	Benchmark benchmark_;
	BenchDaoPtr benchDao_;
public:
	void createBenchmark();
	BenchmarkManagment(std::vector<std::string>& functionsToExecute, const std::string& message, const bool messageIsFile, const int accuracy, BenchDaoPtr benchDao);
	~BenchmarkManagment();
};

} /* namespace Benchmark */

#endif /* BENCHMARK_BENCH_MARK_MANAGEMENT_H_ */
