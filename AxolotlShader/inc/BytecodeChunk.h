#pragma once
#include<map>

struct BytecodeChunk
{
public:
	BytecodeChunk(size_t chunkOffset)
		: ChunkOffset(chunkOffset + 4)
	{

	}

	size_t ChunkOffset;
	std::map<size_t, size_t> Offsets;
	size_t ChunkSize;
};
