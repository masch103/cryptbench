#include "wrong_time_exception.h"

namespace Benchmark {

WrongTimeException::WrongTimeException(const std::string& message) :
		std::logic_error(message) {}


WrongTimeException::~WrongTimeException() {}

} /* namespace CryptoInterface */
