#ifndef DATAACCESSINTERFACE_FILE_NOT_FOUND_EXCEPTION_H_
#define DATAACCESSINTERFACE_FILE_NOT_FOUND_EXCEPTION_H_

#include <stdexcept>

namespace DataAccessInterface {

class FileNotFoundException : public std::logic_error{
public:
	FileNotFoundException(const std::string& message);
	virtual const char* what() const throw() {
		return std::logic_error::what();
	}
	virtual ~FileNotFoundException();
};

} /* namespace DataAccessInterface */

#endif /* DATAACCESSINTERFACE_FILE_NOT_FOUND_EXCEPTION_H_ */
