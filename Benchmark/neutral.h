#ifndef BENCHMARK_NEUTRAL_H_
#define BENCHMARK_NEUTRAL_H_

#include "state.h"

namespace Benchmark {
class TimeStop;
} /* namespace Benchmark */

namespace Benchmark {

class Neutral : public State {
private:
	Benchmark::TimeStop& stopwatch_;
public:
	Neutral(Benchmark::TimeStop& stopwatch);
	void start() override;
	void stop() override;
	microSeconds getPassedTime() override;
	virtual ~Neutral();
};

} /* namespace Benchmark */

#endif /* BENCHMARK_NEUTRAL_H_ */
