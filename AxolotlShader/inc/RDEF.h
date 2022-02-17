#pragma once
#include"AXParser.h"
#include"BytecodeChunk.h"

#include"ShaderObject.h"
#include"ShaderVariable.h"

#include"VariableType.h"
#include"VariableClass.h"

struct BytecodeChunk;
struct RDEF : public BytecodeChunk
{
	struct ConstantBuffer : public ShaderObject
	{
		ConstantBuffer(size_t parent, size_t offset, const std::string& name, uint16_t boundPoint)
			: ShaderObject(parent, offset, name, TYPE_CBUFFER), BoundPoint(boundPoint)
		{

		}
		struct ConstantBufferVariable : public ShaderVariable
		{
		public:
			ConstantBufferVariable(uint16_t type, uint16_t clss, uint32_t variableFlag, uint32_t variableSize, const std::string& name
									, uint16_t row, uint16_t column, uint16_t arraySize, uint16_t structureMemberCount)
				: ShaderVariable(type, clss, variableFlag, variableSize, name),
				mRow(row), mColumn(column), mArraySize(arraySize),
				mStructureMemberCount(structureMemberCount)
			{

			}

			uint16_t GetRow() const { return mRow; }
			uint16_t GetColumn() const { return mColumn; }

			uint16_t GetArraySize() const { return mArraySize; }
			uint16_t GetStructureMemberCount() const { return mStructureMemberCount; }

		private:
			uint16_t mRow;
			uint16_t mColumn;
			uint16_t mArraySize;
			uint16_t mStructureMemberCount;
		};

		uint16_t BoundPoint;
		std::vector<ConstantBufferVariable> Variables;
	};

	RDEF(std::shared_ptr<AXParser> parser);
	~RDEF();

	std::string ToString() const;

private:

	void readConstantBuffers(unsigned int i, size_t firstCbuffer, size_t firstResource);

	void ParseResourceBoundDescription(size_t resourceOffset, size_t firstDescription);

	unsigned int mConstantBufferCount;
	unsigned int mBoundResources;

	unsigned char mMinorVersion;
	unsigned char mMajorVersion;

	unsigned short mShaderType;
	unsigned char mPreshaderFlag;

	std::vector<ConstantBuffer> mConstantBuffers;

	std::string mCreator;
};