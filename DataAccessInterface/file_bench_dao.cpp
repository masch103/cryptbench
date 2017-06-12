#include "file_bench_dao.h"
#include <iostream>
#include "file_not_found_exception.h"

namespace DataAccessInterface {

FileBenchDao::FileBenchDao(const std::string& filePath) : filepath_{filePath} {
	setFstream(filePath);
}

void FileBenchDao::writeBenchResult(
		std::vector<Benchmark::DataObject<std::string>>& dataObjects) {
	for (auto& dataObject : dataObjects) {
		file_ << dataObject;
	}
	file_ << "------------------------------\n";
	std::cout << "Bechmark results are written to : " << filepath_ << std::endl;
}

FileBenchDao::~FileBenchDao() {
}

} /* namespace DataAccessInterface */
