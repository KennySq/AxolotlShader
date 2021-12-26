#pragma once
#include<map>

struct BytecodeChunk
{
	std::map<size_t, size_t> mOffsets;
	size_t mChunkSize;
};
