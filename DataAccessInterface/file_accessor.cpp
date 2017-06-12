#include <iostream>
#include "file_accessor.h"
#include "file_not_found_exception.h"

namespace DataAccessInterface {

FileAccessor::FileAccessor() {

}

void FileAccessor::setFstream(const std::string& filePath) {

	file_.open(filePath,
			std::fstream::out | std::ios::binary | std::ios::in);
	if(!file_.is_open()) {
		throw DataAccessInterface::FileNotFoundException("Can't open file: " + filePath);
	}

}

void FileAccessor::resetFstream() {
	file_.seekg(0, file_.beg);
	file_.clear();
}

FileAccessor::~FileAccessor() {
}

} /* namespace DataAccessInterface */
