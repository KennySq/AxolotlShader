#pragma once
#include"RDEF.h"
#include"ISGN.h"

struct AXBytecode
{
public:
	AXBytecode(const char* path);
	~AXBytecode();
	static std::string GetNextChunk(std::shared_ptr<AXParser> parser);

private:

	std::string ChunkParseProxy(std::string chunk);

	std::unique_ptr<RDEF> mRDEF;

	std::shared_ptr<AXParser> mParser;

};