#pragma once
#include"AXParser.h"
#include"BytecodeChunk.h"

struct BytecodeChunk;
struct RDEF : public BytecodeChunk
{
	struct ConstantBuffer
	{
		struct ConstantBufferVariable
		{
			std::string Name;
			size_t Size;
		};
		std::string Name;
		std::vector<ConstantBufferVariable> Variables;
		
	};

	RDEF(std::shared_ptr<AXParser> parser);
	~RDEF();

private:

	void ParseResourceBoundDescription(size_t resourceOffset, size_t);

	unsigned int mConstantBufferCount;
	unsigned int mBoundResources;

	unsigned char mMinorVersion;
	unsigned char mMajorVersion;

	unsigned short mShaderType;
	unsigned char mPreshaderFlag;

	std::shared_ptr<AXParser> mParser;

	std::vector<ConstantBuffer> mConstantBuffers;
};