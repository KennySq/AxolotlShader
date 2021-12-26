#pragma once

struct AXParser
{
public:
	AXParser(const char* path);
	~AXParser();
	static std::shared_ptr<AXParser> OpenFile(const char* path);

	std::string Read(size_t from, size_t to);
	char Read();
private:

	void jump();

	char mByte;
	size_t mLast;

	std::ifstream mFile;
	unsigned int mReadIndex;
};