#include<pch.h>
#include"AXBytecode.h"
#include"Util.h"

AXBytecode::AXBytecode(const char* path)
{
	mParser = AXParser::OpenFile(path);

	AXParser::ByteBlock header = mParser->Read(0, 4);
	AXParser::ByteBlock checksum = mParser->Read(4);
	AXParser::ByteBlock fileSize = mParser->Read(24);

	mRDEF = std::make_unique<RDEF>();
	std::cout << header.ToString() << " | " << checksum.ToNumericString(10) << " | " <<  fileSize.ToNumericString(16) << '\n';
}

AXBytecode::~AXBytecode()
{
}
