#pragma once
#include"AXParser.h"

struct AXBytecode
{
public:
	AXBytecode(const char* path);
	~AXBytecode();
	static std::string GetNextChunk(std::shared_ptr<AXParser> parser);

private:

	std::string ChunkParseProxy(std::string chunk);

	std::shared_ptr<AXParser> mParser;

};