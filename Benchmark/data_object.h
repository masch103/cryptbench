#ifndef BENCHMARK_DATA_OBJECT_H_
#define BENCHMARK_DATA_OBJECT_H_

#include <string>
#include <iostream>
#include <chrono>

namespace Benchmark {

using microSeconds = std::chrono::microseconds;
using milliSeconds = std::chrono::milliseconds;
using seconds = std::chrono::seconds;

template<typename Value>
class DataObject {
private:
	std::string name_;
	microSeconds runtime_;
	Value value_;
public:
	DataObject(std::string name, microSeconds runtime, Value value) :
			name_(name), runtime_(runtime), value_(value) {

	}
	;
	friend std::ostream& operator<<(std::ostream& os,
			DataObject<Value> const& dataObject) {
		seconds s = std::chrono::duration_cast<seconds>(dataObject.getRuntime());
		milliSeconds ms = std::chrono::duration_cast<milliSeconds>(dataObject.getRuntime() % seconds(1));
		microSeconds micSec = std::chrono::duration_cast<microSeconds>(dataObject.getRuntime() % milliSeconds(1));
		os << "Name: " << dataObject.getName() << "\n Digest: "
				<< dataObject.getValue() << "\n Runtime: "
				<< s.count() << "s" << " " << ms.count() << "ms" << " " << micSec.count() << "us\n\n";
		return os;
	}
	void setName(std::string name) {
		name_ = name;
	}
	void setRuntime(microSeconds runtime) {
		runtime_ = runtime;
	}
	void setValue(Value value) {
		value_ = value;
	}
	std::string getName() const {
		return name_;
	}
	microSeconds getRuntime() const {
		return runtime_;
	}
	Value getValue() const {
		return value_;
	}
	~DataObject() {
	}
	;
};

} /* namespace Benchmark */

#endif /* BENCHMARK_DATA_OBJECT_H_ */
