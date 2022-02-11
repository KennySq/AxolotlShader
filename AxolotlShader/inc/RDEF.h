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
			uint16_t Row;
			uint16_t Column;
			uint16_t ArraySize;
			uint16_t StructureMemberCount;
			uint16_t VariableType;
			uint16_t VariableClass;
		};
		std::string Name;
		std::vector<ConstantBufferVariable> Variables;
	};

	RDEF(std::shared_ptr<AXParser> parser);
	~RDEF();

	std::string ToString() const;

private:

	void ParseResourceBoundDescription(size_t resourceOffset, size_t firstDescription);

	unsigned int mConstantBufferCount;
	unsigned int mBoundResources;

	unsigned char mMinorVersion;
	unsigned char mMajorVersion;

	unsigned short mShaderType;
	unsigned char mPreshaderFlag;

	std::shared_ptr<AXParser> mParser;

	std::vector<ConstantBuffer> mConstantBuffers;
};