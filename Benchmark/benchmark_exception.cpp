#include "benchmark_exception.h"

BenchmarkException::BenchmarkException(const std::string& message) : std::logic_error(message) {}

BenchmarkException::~BenchmarkException() {}

