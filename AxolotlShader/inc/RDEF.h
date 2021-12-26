#pragma once
#include"AXParser.h"
#include"BytecodeChunk.h"

struct BytecodeChunk;
struct RDEF : public BytecodeChunk
{
	void Parse(size_t start, size_t end, std::unique_ptr<AXParser>&& parser);
private:

	unsigned int mConstantBufferCount;
	unsigned int mBoundResources;

	unsigned char mMinorVersion;
	unsigned char mMajorVersion;

	unsigned short mShaderType;
	unsigned char mPreshaderFlag;
};