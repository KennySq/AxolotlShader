#include<pch.h>
#include"AXBytecode.h"

AXBytecode::AXBytecode(const char* path)
{
	mParser = AXParser::OpenFile(path);

	std::string header = mParser->Read(0, 4);
	std::string checksum = mParser->Read(4, 19);
	std::string fileSize = mParser->Read(24, 25);

	std::string rdef = mParser->Read(52, 56);
	//mParser->Read();
	mRDEF = std::make_unique<RDEF>();
	std::cout << header << " | " << std::stoi(checksum) << " | " << std::dec << fileSize << '\n';
	
}

AXBytecode::~AXBytecode()
{
}
