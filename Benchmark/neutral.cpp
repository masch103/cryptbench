#include "neutral.h"
#include "time_stop.h"
#include "wrong_time_exception.h"
#include <chrono>

#include "running.h"




namespace Benchmark {

Neutral::Neutral(Benchmark::TimeStop& stopwatch) : stopwatch_(stopwatch){

}


void Neutral::start() {
	stopwatch_.setStartTime(std::chrono::high_resolution_clock::now());
	stopwatch_.setState(std::make_shared<Running>(stopwatch_));
}

void Neutral::stop() {
	throw WrongTimeException("Timer not started, please start timer");
}

microSeconds Neutral::getPassedTime() {
	throw WrongTimeException("Timer not started, please start timer");
}


Neutral::~Neutral() {}

} /* namespace Benchmark */
