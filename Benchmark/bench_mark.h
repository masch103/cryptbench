#ifndef BENCHMARK_BENCH_MARK_H_
#define BENCHMARK_BENCH_MARK_H_

#include "data_object.h"
#include "time_stop.h"
#include <vector>



namespace Benchmark {

using FunctionVector = std::vector<std::string>;
using DataObjectVector = std::vector<DataObject<std::string>>;

class Benchmark {
private:
	TimeStop stopwatch_{};
	DataObjectVector dataObjects_{};
	FunctionVector& functionsToExecute_;
	const std::string& message_;
	const bool messageIsFile_;
	//Determinate the accuracy of the benchmark, the higher the value the higher the accuracy
	const int accuracy_;
	void validateBenchmark();
	void changeProcessPriortiy();
public:
	DataObjectVector& getDataObjects() {
		return dataObjects_;
	}
	Benchmark(FunctionVector& functionsToExecute, const std::string& message, const bool messageIsFile, const int accuracy);
	void executeBenchmark();
	~Benchmark();
};

} /* namespace Benchmark */

#endif /* BENCHMARK_BENCH_MARK_H_ */
