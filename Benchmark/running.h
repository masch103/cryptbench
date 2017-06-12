#ifndef BENCHMARK_RUNNING_H_
#define BENCHMARK_RUNNING_H_

#include "state.h"

namespace Benchmark {
class TimeStop;
} /* namespace Benchmark */

namespace Benchmark {

class Running : public State {
private:
	Benchmark::TimeStop& stopwatch_;
public:
	Running(Benchmark::TimeStop& stopwatch);
	void start() override;
	void stop() override;
	microSeconds getPassedTime() override;
	virtual ~Running();
};

} /* namespace Benchmark */

#endif /* BENCHMARK_RUNNING_H_ */
