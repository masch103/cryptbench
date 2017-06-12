#ifndef BENCHMARK_STOPPED_H_
#define BENCHMARK_STOPPED_H_

#include "state.h"

namespace Benchmark {
class TimeStop;
} /* namespace Benchmark */

namespace Benchmark {

class Stopped : public State {
private:
	Benchmark::TimeStop& stopwatch_;
public:
	Stopped(Benchmark::TimeStop& stopwatch);
	void start() override;
	void stop() override;
	microSeconds getPassedTime() override;
	virtual ~Stopped();
};

} /* namespace Benchmark */

#endif /* BENCHMARK_STOPPED_H_ */
