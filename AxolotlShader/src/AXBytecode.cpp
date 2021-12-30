#include<pch.h>
#include"AXBytecode.h"
#include"Decoder.h"
#include"Util.h"
#include"Header.h"

AXBytecode::AXBytecode(const char* path)
{
	mParser = AXParser::OpenFile(path);
	Header head = Header(mParser);
	std::string headNext = GetNextChunk(mParser);

	ChunkParseProxy(headNext);


}

AXBytecode::~AXBytecode()
{
}

std::string AXBytecode::GetNextChunk(std::shared_ptr<AXParser> parser)
{
	uint32_t nextDescription = parser->ReadUint32();
	std::string nextChunk = Decoder::ToFourString(nextDescription);

	return nextChunk;
}

std::string AXBytecode::ChunkParseProxy(std::string chunk)
{
	if (chunk == "")
	{
		return "";
	}

	if (chunk == "RDEF") // RDEF chunk
	{
		RDEF rdef = RDEF(mParser);
	}

	return GetNextChunk(mParser);
}
