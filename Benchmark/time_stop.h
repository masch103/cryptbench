#ifndef BENCHMARK_TIME_STOP_H_
#define BENCHMARK_TIME_STOP_H_

#include "state.h"
#include <chrono>
#include <memory>

namespace Benchmark {

using microSeconds = std::chrono::microseconds;
using milliSeconds = std::chrono::milliseconds;
using seconds = std::chrono::seconds;
using Time = std::chrono::time_point<std::chrono::high_resolution_clock>;
using statePointer = std::shared_ptr<Benchmark::State>;

class TimeStop {
private:
	Time startTime_;
	Time endTime_;
	statePointer innerState_;
public:
	TimeStop();
	Time getStartTime() const {
		return startTime_;
	}
	;
	Time getEndTime() const {
		return endTime_;
	}
	;
	void setStartTime(Time startTime) {
		startTime_ = startTime;
	}
	;
	void setEndTime(Time endTime) {
		endTime_ = endTime;
	}
	;
	//function template is used, because auto is not
        ///supported in function signature on every compiler
	template<class T>
	void setState(T newState) {
		innerState_ = std::move(newState);
	}
	;
	void start() {
		innerState_->start();
	}
	;
	void stop() {
		innerState_->stop();
	}
	;
	microSeconds getPassedTime() {
		return innerState_->getPassedTime();
	}
	virtual ~TimeStop();
};

} /* namespace Benchmark */

#endif /* BENCHMARK_TIME_STOP_H_ */
