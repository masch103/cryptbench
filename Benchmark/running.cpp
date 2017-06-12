#include "running.h"
#include "time_stop.h"
#include "wrong_time_exception.h"
#include <chrono>

#include "stopped.h"

namespace Benchmark {

Running::Running(Benchmark::TimeStop& stopwatch) : stopwatch_(stopwatch){}

void Running::start() {
	throw WrongTimeException("Timer already started, please clear timer");
}

void Running::stop() {
	stopwatch_.setEndTime(std::chrono::high_resolution_clock::now());
	stopwatch_.setState(std::make_shared<Stopped>(stopwatch_));
}

microSeconds Running::getPassedTime() {
	throw WrongTimeException("Timer still running");
}

Running::~Running() {}

} /* namespace Benchmark */
