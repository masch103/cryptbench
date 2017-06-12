#ifndef CRYPTOINTERFACE_STREAM_READER_H_
#define CRYPTOINTERFACE_STREAM_READER_H_

#include <fstream>

namespace CryptoInterface {

class StreamReader {
private:
	std::istream& inputStream_;
	void set_istream(std::istream& inputStream);
	void resetIstream();
public:
	StreamReader(std::istream& inputStream);
	bool read(unsigned char* buffer, unsigned int bufferSize);
	int getLastReadSize();
	virtual ~StreamReader();
};

} /* namespace StandaloneHashFunctions */

#endif /* DATAACCESSINTERFACE_FILE_READER_H_ */
