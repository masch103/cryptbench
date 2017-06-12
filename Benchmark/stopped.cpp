#include "stopped.h"
#include "time_stop.h"
#include "wrong_time_exception.h"
#include <chrono>

#include "neutral.h"


namespace Benchmark {

Stopped::Stopped(Benchmark::TimeStop& stopwatch) : stopwatch_(stopwatch){}

void Stopped::start() {
	throw WrongTimeException("Please clear timer");
}

void Stopped::stop() {
	throw WrongTimeException("Please clear timer");
};

microSeconds Stopped::getPassedTime() {
	microSeconds result = std::chrono::duration_cast<microSeconds>(stopwatch_.getEndTime() - stopwatch_.getStartTime());
	stopwatch_.setState(std::make_shared<Neutral>(stopwatch_));
	return result;
}

Stopped::~Stopped() {}

} /* namespace Benchmark */
