#include"pch.h"
#include"AXParser.h"

#include"RDEF.h"

AXParser::AXParser(const char* path)
{
	mFile.open(path, std::ifstream::binary);
	
	if (!mFile)
	{
		std::cout << "Failed.\n";
	}

}

AXParser::~AXParser()
{
}

std::shared_ptr<AXParser> AXParser::OpenFile(const char* path)
{
	return std::make_shared<AXParser>(path);
}

std::string AXParser::Read(size_t from, size_t to)
{
	mFile.seekg(from);

	std::string buffer;
	int count = to - from;
	int index = 0;

	buffer.resize(count);

	while (index < count)
	{
		int buf;
		buf = mFile.get();

		buffer[index++] = buf;
	}

	mLast = to;

	jump();

	return buffer;
}

char AXParser::Read()
{
	mFile.read(&mByte, 1);

	return mByte;
}

void AXParser::jump()
{
	size_t idx = mLast;
	while (mFile.eof() == false)
	{
		char b;
		mFile.read(&b, 1);

		if (b != 0x00)
		{
			mFile.seekg(idx);
			mLast = idx;
			break;
		}

		idx++;
	}


}