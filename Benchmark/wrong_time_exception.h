#ifndef BENCHMARK_WRONG_TIME_EXCEPTION_H_
#define BENCHMARK_WRONG_TIME_EXCEPTION_H_

#include <string>
#include <stdexcept>

namespace Benchmark {

class WrongTimeException : public std::logic_error {
public:
	WrongTimeException(const std::string& message);
	virtual const char* what() const throw(){
		return std::logic_error::what();
	}
	virtual ~WrongTimeException();
};

} /* namespace CryptoInterface */

#endif /* BENCHMARK_WRONG_TIME_EXCEPTION_H_ */
