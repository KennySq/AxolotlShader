#include<pch.h>
#include"RDEF.h"

RDEF::RDEF(std::shared_ptr<AXParser> parser)
	: mParser(parser), BytecodeChunk(parser->GetByteIndex())
{
	uint32_t chunkSize = parser->ReadUint32();
	uint32_t cbufferCount = parser->ReadUint32();
	uint32_t firstCbufferOffset = parser->ReadUint32();
	uint32_t resourceCount = parser->ReadUint32();
	uint32_t firstResourceOffset = parser->ReadUint32();
	unsigned char minor = parser->ReadUint8();
	unsigned char major = parser->ReadUint8();

	ChunkSize = chunkSize;
	mConstantBufferCount = cbufferCount;
	mBoundResources = resourceCount;

	mMajorVersion = major;
	mMinorVersion = minor;
	
	uint16_t shaderType = parser->ReadUint16();
	uint32_t preshaderFlag = parser->ReadUint32();
	uint32_t creatorStringOffset = parser->ReadUint32();

	mShaderType = shaderType;

	parser->Jump(sizeof(uint64_t) * 4 * resourceCount);

	for (unsigned int i = 0; i < cbufferCount; i++)
	{
		readConstantBuffers(i, firstCbufferOffset, firstResourceOffset);
	}

	parser->Jump(ChunkOffset, creatorStringOffset);
	std::string creator = parser->ReadString();


}

RDEF::~RDEF()
{
}

std::string RDEF::ToString() const
{
	std::string str = "";
	str += "RDEF Chunk\n";
	str += " - Chunk Size : " + std::to_string(ChunkSize) + '\n';

	switch (mShaderType)
	{
	case 0xFFFE:
	{
		str += " - Shader Model : VS_" + mMajorVersion + '_' + mMinorVersion + '\n';
	}
	break;
	case 0xFFFF:
	{
		str += " - Shader Model : PS_" + mMajorVersion + '_' + mMinorVersion + '\n';

	}
	break;

	case 0x4753:
	{
		str += " - Shader Model : GS_" + mMajorVersion + '_' + mMinorVersion + '\n';
	}
	break;

	}

	str += " - Constant Buffer Count : " + std::to_string(mConstantBufferCount) + '\n';
	str += " - Bound Resources : " + std::to_string(mBoundResources) + '\n';
	
	return str;
}

void RDEF::readConstantBuffers(unsigned int i, size_t firstCbuffer, size_t firstResource)
{
	int cbufferDescriptorOffset = (i * 24);
	int resourceDescriptorOffset = (i * 32);

	mParser->Jump(ChunkOffset, firstCbuffer + cbufferDescriptorOffset);

	uint32_t cbufferNameOffset = mParser->ReadUint32();
	uint32_t variableCount = mParser->ReadUint32();
	uint32_t firstVariableDescriptionOffset = mParser->ReadUint32();
	uint32_t cbufferSize = mParser->ReadUint32();
	uint32_t cbufferFlag = mParser->ReadUint32();
	uint32_t cbufferType = mParser->ReadUint32();

	mParser->Jump(ChunkOffset, cbufferNameOffset);
	std::string cbufferName = mParser->ReadString();

	ConstantBuffer cbuffer = ConstantBuffer(ChunkOffset, firstCbuffer + cbufferDescriptorOffset, cbufferName);

	mParser->Jump(ChunkOffset, firstResource + resourceDescriptorOffset);

	uint32_t resourceBoundName = mParser->ReadUint32();
	uint32_t shaderInputType = mParser->ReadUint32();
	uint32_t resourceReturnType = mParser->ReadUint32();
	uint32_t resourceViewDimension = mParser->ReadUint32();
	uint32_t sampleCount = mParser->ReadUint32();
	uint32_t bindPoint = mParser->ReadUint32();
	uint32_t bindCount = mParser->ReadUint32();
	uint32_t shaderInputFlag = mParser->ReadUint32();




	for (unsigned int j = 0; j < variableCount; j++)
	{
		mParser->Jump(ChunkOffset, firstVariableDescriptionOffset + (j * 24));


		uint32_t variableNameOffset = mParser->ReadUint32();
		uint32_t cbufferOffset = mParser->ReadUint32();

		uint32_t variableSize = mParser->ReadUint32();
		uint32_t variableFlag = mParser->ReadUint32(); // 2 means has been used.

		uint32_t variableTypeOffset = mParser->ReadUint32();
		uint32_t defaultOffset = mParser->ReadUint32();

		size_t readPoint = mParser->GetByteIndex();

		mParser->Jump(ChunkOffset, variableNameOffset);

		std::string variableName = mParser->ReadString();

		mParser->Jump(ChunkOffset, variableTypeOffset);

		uint16_t variableClass = mParser->ReadUint16();
		uint16_t variableType = mParser->ReadUint16();

		uint16_t matrixRowCount = mParser->ReadUint16();
		uint16_t matrixColumnCount = mParser->ReadUint16();
		uint16_t arrayCount = mParser->ReadUint16();
		uint16_t structureMemberCount = mParser->ReadUint16();
		uint16_t firstMemberOffset = mParser->ReadUint16();
		uint16_t unknown16 = mParser->ReadUint16();

		ConstantBuffer::ConstantBufferVariable variable =
			ConstantBuffer::ConstantBufferVariable(variableFlag, variableSize, variableName,
				matrixRowCount, matrixColumnCount, arrayCount, structureMemberCount);

		cbuffer.Variables.push_back(variable);

		if (i != 0)
		{
			mParser->Jump(0, readPoint);
		}
	}

	mConstantBuffers.push_back(cbuffer);
}

void RDEF::ParseResourceBoundDescription(size_t resourceOffset, size_t firstDescription)
{

}
