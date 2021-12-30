#include "pch.h"
#include "Header.h"
#include"AXParser.h"
#include"Decoder.h"

Header::Header(std::shared_ptr<AXParser> parser)
	: mParser(parser)
{
	uint32_t headDescription = parser->ReadUint32();
	std::string headName = Decoder::ToFourString(headDescription);

	uint64_t checksum = mParser->ReadUint64();
	uint64_t checksum2 = mParser->ReadUint64();
	uint32_t somethingOne = mParser->ReadUint32();
	uint32_t fileSize = mParser->ReadUint32();
	uint32_t chunkCount = mParser->ReadUint32();
	
	std::cout << headName << "\n - File Size: " << fileSize << " bytes\n - Chunk Count : " << chunkCount << '\n';

	uint32_t unused0 = mParser->ReadUint32();
	uint32_t unused1 = mParser->ReadUint32();
	uint32_t unused2 = mParser->ReadUint32();
	uint32_t unused3 = mParser->ReadUint32();
	uint32_t unused4 = mParser->ReadUint32();
		
}