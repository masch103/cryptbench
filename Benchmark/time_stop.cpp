#include "time_stop.h"
#include "neutral.h"

namespace Benchmark {

TimeStop::TimeStop() {
	setState(std::make_shared<Benchmark::Neutral>(*this));
}

TimeStop::~TimeStop() {
}



} /* namespace Benchmark */
