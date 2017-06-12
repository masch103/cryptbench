#include "file_not_found_exception.h"

namespace DataAccessInterface {

FileNotFoundException::FileNotFoundException(const std::string& message) : std::logic_error(message) {}

FileNotFoundException::~FileNotFoundException() {}

} /* namespace DataAccessInterface */
