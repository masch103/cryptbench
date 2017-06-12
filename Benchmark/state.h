#ifndef BENCHMARK_STATE_H_
#define BENCHMARK_STATE_H_

#include <chrono>



namespace Benchmark {

using microSeconds = std::chrono::microseconds;

class State {
public:
	State();
	virtual void start() = 0;
	virtual void stop() = 0;
	virtual microSeconds getPassedTime() = 0;
	virtual ~State();
};



} /* namespace Benchmark */

#endif /* BENCHMARK_STATE_H_ */
