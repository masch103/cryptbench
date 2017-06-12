#ifndef BENCHMARK_BENCHMARK_EXCEPTION_H_
#define BENCHMARK_BENCHMARK_EXCEPTION_H_

#include <stdexcept>

class BenchmarkException : public std::logic_error{
public:
	BenchmarkException(const std::string& message);
	virtual const char* what() const throw(){
			return std::logic_error::what();
		}
	virtual ~BenchmarkException();
};

#endif /* BENCHMARK_BENCHMARK_EXCEPTION_H_ */
