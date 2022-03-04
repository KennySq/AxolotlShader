#include<pch.h>
#include"AXBytecode.h"
#include"Decoder.h"
#include"Util.h"
#include"Header.h"

#include"RDEF.h"
#include"ISGN.h"
#include"OSGN.h"
#include"SHDR.h"

AXBytecode::AXBytecode(const char* path)
{
	mParser = AXParser::OpenFile(path);
	Header head = Header(mParser);
	std::string rdefString = GetNextChunk(mParser);

	std::string isgnString = ChunkParseProxy(rdefString);
	std::string osgnString = ChunkParseProxy(isgnString);
	std::string shdrChunk = ChunkParseProxy(osgnString);
	std::string nextChunk = ChunkParseProxy(shdrChunk);
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
		
		std::cout << rdef.ToString() << '\n';
	}

	else if (chunk == "ISGN")
	{
		ISGN isgn = ISGN(mParser);

		std::cout << isgn.ToString() << '\n';
	}

	else if (chunk == "OSGN")
	{
		OSGN osgn = OSGN(mParser);

		std::cout << osgn.ToString() << '\n';
	}
	else if (chunk == "SHDR")
	{
		SHDR shdr = SHDR(mParser);

		std::cout << shdr.ToString() << '\n';
	}

	return GetNextChunk(mParser);
}
