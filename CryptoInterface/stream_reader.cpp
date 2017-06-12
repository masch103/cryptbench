#include "stream_reader.h"

namespace CryptoInterface {

StreamReader::StreamReader(std::istream& inputStream) :
		inputStream_(inputStream) {
}



void StreamReader::set_istream(std::istream& inputStream) {
	//this->inputStream(inputStream);
}

void StreamReader::resetIstream() {
	inputStream_.seekg(0, inputStream_.beg);
	inputStream_.clear();
}


bool StreamReader::read(unsigned char* buffer, unsigned int bufferSize) {

	inputStream_.read(reinterpret_cast<char*> (buffer), static_cast<int>(bufferSize));
	return inputStream_.eof() && inputStream_.fail();

}



int StreamReader::getLastReadSize() {
	return inputStream_.gcount();
}

StreamReader::~StreamReader() {}

} /* namespace CryptoInterface */
