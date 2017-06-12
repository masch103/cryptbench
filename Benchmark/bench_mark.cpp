#include "bench_mark.h"
#include "benchmark_exception.h"
#include "hashfunction_factory.h"
#include "sys/resource.h"
#include "wrong_time_exception.h"
#include <chrono>
#include <iostream>
#include <memory>

namespace Benchmark {

using HashPointer = std::unique_ptr<CryptoInterface::HashFunction>;

Benchmark::Benchmark(FunctionVector& fte, const std::string& message,
		const bool messageIsFile, const int accuracy = 3) :
		functionsToExecute_(fte), message_(message), messageIsFile_(
				messageIsFile), accuracy_(accuracy) {
}

void Benchmark::changeProcessPriortiy() {
	//set process priority on highest possible value
	/*
	 * Keep in mind: This is only the niceness value,
	 * there is no guaranty on operating system level
	 */
	if (setpriority(PRIO_PROCESS, 0, -20) < 0) {
		//throw BenchmarkException("Can't set process priority. Was the program started as root?");
		std::cout
				<< "Can't set process priority. Was the program started as root? Without root privileges the Benchmark is less accurate\n";
	}
}

void Benchmark::validateBenchmark() {
	if (functionsToExecute_.empty()) {
		throw BenchmarkException("No functions specified");
	}
}

void Benchmark::executeBenchmark() {
	Benchmark::validateBenchmark();
	Benchmark::changeProcessPriortiy();
	if (functionsToExecute_.at(0) == "ALL") {
		functionsToExecute_ = CryptoInterface::supportedHashfunctions;
	}

	for (auto& function : functionsToExecute_) {
		HashPointer hashPointer { };
		try {
			hashPointer =
					CryptoInterface::HashFunctionFactory::createHashfunction(
							function);
		} catch (std::invalid_argument& e) {
			std::cout << e.what() << std::endl;
		}
		std::string currentMessageDigest { };
		std::chrono::microseconds passedTime { };
		std::chrono::microseconds emptyTime { };
		for (int i = 0; i < accuracy_; i++) {
			try {
				//empty measurement
				stopwatch_.start();
				stopwatch_.stop();
				emptyTime = stopwatch_.getPassedTime();

				stopwatch_.start();
				currentMessageDigest = hashPointer->getMessageDigest(message_,
						messageIsFile_);
				stopwatch_.stop();
			} catch (WrongTimeException& e) {
				std::cout << e.what() << std::endl;
			}
			passedTime += (stopwatch_.getPassedTime() - emptyTime);
		}
		passedTime /= accuracy_;
		DataObject<std::string> dataObject { function, passedTime,
				currentMessageDigest };
		dataObjects_.push_back(dataObject);
	}
}

Benchmark::~Benchmark() {
}

} /* namespace CryptoInterface */
