#pragma once
#include<map>
#include"AXParser.h"

struct BytecodeChunk
{
public:
	BytecodeChunk(size_t chunkOffset, std::shared_ptr<AXParser> parser)
		: ChunkOffset(chunkOffset + 4), Parser(parser)
	{

	}

	size_t ChunkOffset;
	std::map<size_t, size_t> Offsets;
	size_t ChunkSize;
	std::shared_ptr<AXParser> Parser;

};
