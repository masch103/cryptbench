#include "file_reader.h"

namespace DataAccessInterface {

FileReader::FileReader(const std::string& filePath) {
	setIfstream(filePath);
}

FileReader::~FileReader() {}

bool FileReader::verifyFileExistence(const std::string& filePath) {
	std::ifstream file(filePath, std::ios::in);
	return file.is_open();
}

void FileReader::setIfstream(const std::string& filePath) {
	if(verifyFileExistence(filePath)){
		file_.open(filePath, std::ios::in|std::ios::binary);
	}else{
		//TODO: Exception Handling
	}
}

void FileReader::resetIfstream(){
	file_.seekg(0, file_.beg);
	file_.clear();
}

bool FileReader::read(unsigned char* buffer, unsigned int bufferSize){
	bool eof_flag = file_.eof() && file_.fail();
	if(!eof_flag){
		file_.read((char*)buffer, bufferSize);
	}else{
		//input stream ended; set to beginning
		resetIfstream();
	}
	return eof_flag;
}



} /* namespace StandaloneHashFunctions */
