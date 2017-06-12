#ifndef DATAACCESSINTERFACE_FILE_ACCESSOR_H_
#define DATAACCESSINTERFACE_FILE_ACCESSOR_H_

#include <fstream>
#include <iostream>
#include <ios>
#include <string>

namespace DataAccessInterface {

class FileAccessor {
protected:
	std::fstream file_{};
public:
	FileAccessor();
	std::fstream& getIfstream() {
		return file_;
	}
	void setFstream(const std::string& filePath);
	void resetFstream();
	virtual~FileAccessor();
};

} /* namespace CryptoInterface */

#endif /* DATAACCESSINTERFACE_FILE_ACCESSOR_H_ */
