#pragma once

struct AXParser
{
	struct ByteBlock
	{
		std::vector<unsigned char> Bytes;
		size_t From;
		size_t To;

		std::string ToString() const;
		std::string ToNumericString(int base) const;
	};


public:
	AXParser(const char* path);
	~AXParser();
	static std::shared_ptr<AXParser> OpenFile(const char* path);

	ByteBlock Read(size_t from, size_t to);
	ByteBlock Read(size_t from); // this method will reads data until encounters 0x00 (NULL).
	char Read();
private:

	void jump();

	char mByte;
	size_t mLast;

	std::ifstream mFile;
	unsigned int mReadIndex;
};