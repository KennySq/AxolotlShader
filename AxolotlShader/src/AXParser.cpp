#pragma once
#include<pch.h>
#include"AXParser.h"

AXParser::AXParser(const char* path)
	: mIndex(0)
{
	mFile.open(path, std::ifstream::binary);
	
	if (!mFile)
	{
		std::cout << "Failed.\n";
	}

	mFile.seekg(0, mFile.end);

	unsigned int binarySize = mFile.tellg();

	mFile.seekg(0, mFile.beg);

	mRaw = new unsigned char[binarySize];

	mFile.read((char*)mRaw, binarySize);
	mFile.close();
	mSize = binarySize;

	return;
}

AXParser::~AXParser()
{
}

std::shared_ptr<AXParser> AXParser::OpenFile(const char* path)
{
	return std::make_shared<AXParser>(path);
}

std::string AXParser::ByteBlock::ToString() const
{
	std::string str(Bytes.begin(), Bytes.end());

	return str;
}

std::string AXParser::ByteBlock::ToNumericString(int base) const
{
	std::string str;
	size_t size = Bytes.size();

	for (int i = size - 1; i >= 0; i--)
	{
		char buf[256];
		_itoa_s(Bytes[i], buf, 256, base);
		
		for (unsigned int j = 0; j < 256; j++)
		{

			if (buf[j] == '\0')
			{
				break;
			}
			str.push_back(buf[j]);
			
		}

		str.push_back(' ');
	}
	
	return str;
}