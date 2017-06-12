#ifndef DATAACCESSINTERFACE_FILE_READER_H_
#define DATAACCESSINTERFACE_FILE_READER_H_

#include <fstream>
#include <string>

namespace DataAccessInterface {

class FileReader {
private:
	std::ifstream file_;
	bool verifyFileExistence(const std::string& filePath);
	void setIfstream(const std::string& filePath);
	void resetIfstream();
public:
	FileReader(const std::string& filePath);
	virtual ~FileReader();
	bool read(unsigned char* buffer, unsigned int bufferSize);
};

}

#endif /* DATAACCESSINTERFACE_FILE_READER_H_ */
