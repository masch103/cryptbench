#ifndef DATAACCESSINTERFACE_BENCH_DAO_H_
#define DATAACCESSINTERFACE_BENCH_DAO_H_

#include <map>
#include <string>
#include <vector>
#include "data_object.h"

namespace DataAccessInterface {

class BenchDao {
public:
	BenchDao();
	virtual void writeBenchResult(std::vector<Benchmark::DataObject<std::string>>& dataObjects) = 0;
	virtual ~BenchDao();
};

} /* namespace CryptoInterface */

#endif /* DATAACCESSINTERFACE_BENCH_DAO_H_ */
