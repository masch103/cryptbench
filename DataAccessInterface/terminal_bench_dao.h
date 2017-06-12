#ifndef DATAACCESSINTERFACE_TERMINAL_BENCH_DAO_H_
#define DATAACCESSINTERFACE_TERMINAL_BENCH_DAO_H_

#include "bench_dao.h"

namespace DataAccessInterface{

class TerminalBenchDao : public BenchDao {
public:
	TerminalBenchDao();
	void writeBenchResult(std::vector<Benchmark::DataObject<std::string>>& dataObjects) override;
	virtual ~TerminalBenchDao();
};

} /* namespace DataAccessInterface */

#endif /* DATAACCESSINTERFACE_TERMINAL_BENCH_DAO_H_ */
