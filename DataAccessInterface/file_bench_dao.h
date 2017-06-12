#ifndef DATAACCESSINTERFACE_FILE_BENCH_DAO_H_
#define DATAACCESSINTERFACE_FILE_BENCH_DAO_H_

#include "bench_dao.h"
#include "file_accessor.h"

namespace DataAccessInterface {

class FileBenchDao : public BenchDao, public FileAccessor{
private:
	const std::string& filepath_;
public:
	FileBenchDao(const std::string& filePath);
	void writeBenchResult(std::vector<Benchmark::DataObject<std::string>>& dataObjects) override;
	virtual ~FileBenchDao();
};

} /* namespace DataAccessInterface */

#endif /* DATAACCESSINTERFACE_FILE_BENCH_DAO_H_ */
