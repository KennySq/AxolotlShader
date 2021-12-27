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

AXParser::ByteBlock AXParser::Read(size_t from, size_t to)
{
	mFile.seekg(from);

	ByteBlock block;

	block.From = from;
	block.To = to;

	int count = to - from;
	int index = 0;

	block.Bytes.resize(count);

	while (index < count)
	{
		int buf;
		buf = mFile.get();

		block.Bytes[index++] = buf;
	}

	mLast = to;

	jump();

	return block;
}

AXParser::ByteBlock AXParser::Read(size_t from)
{
	mFile.seekg(from);

	ByteBlock block;

	block.From = from;

	int index = 0;

	while (true)
	{
		int buf;
		buf = mFile.get();

		if (buf == 0x00)
		{
			break;
		}

		block.Bytes.push_back(buf);
	}

	mLast = block.From + index;
	block.To = mLast;

	jump();

	return block;
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
