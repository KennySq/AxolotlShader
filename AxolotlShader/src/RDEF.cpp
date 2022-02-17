#include<pch.h>
#include"RDEF.h"

RDEF::RDEF(std::shared_ptr<AXParser> parser)
	: BytecodeChunk(parser->GetByteIndex(), parser)
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
	mCreator = parser->ReadString();
}

RDEF::~RDEF()
{
}

std::string RDEF::ToString() const
{
	std::string str = "";
	str += mCreator + '\n';
	std::string smString = " - Shader Model : ";

	switch (mShaderType)
	{
	case 0xFFFE:
	{
		smString += std::string(" : VS_") + std::to_string(mMajorVersion) + '_' + std::to_string(mMinorVersion) + '\n';
	}
	break;
	case 0xFFFF:
	{
		smString += std::string(" : PS_") + std::to_string(mMajorVersion) + '_' + std::to_string(mMinorVersion) + '\n';
	}
	break;

	case 0x4753:
	{
		str += " - Shader Model : GS_" + mMajorVersion + '_' + mMinorVersion + '\n';
	}
	break;

	}

	str += smString;

	str += " - Constant Buffer Count : " + std::to_string(mConstantBufferCount) + '\n';
	str += " - Bound Resources : " + std::to_string(mBoundResources) + '\n';
	
	str += std::string(" - Constant Buffers\n");

	for (ConstantBuffer cb : mConstantBuffers)
	{
		str += "\t";
		
		str += std::string(" - Bind Point : ") + std::to_string(cb.BoundPoint) + '\n';
		for (ConstantBuffer::ConstantBufferVariable var : cb.Variables)
		{
			uint32_t size = var.GetVariableSize();
			uint16_t clss = var.GetVariableClass();
			
			str += std::string("\t\t") + var.GetName();
			if (var.GetVariableFlag() == 2)
			{
				str += " (USED)";
			}

			str += '\n';

			str += std::string("\t\t - Varialbe Size : ") + std::to_string(size);
			str += '\n';

			if (clss == eVariableClass::CLASS_MATRIX_COLUMNS || clss == eVariableClass::CLASS_MATRIX_ROWS)
			{
				str += std::string("\t\t - Rows : ") + std::to_string(var.GetRow()) + '\n';
				str += std::string("\t\t - Columns : ") + std::to_string(var.GetColumn()) + '\n';

			}

			str += '\n';

		}

		str += '\n';
	}

	return str;
}

void RDEF::readConstantBuffers(unsigned int i, size_t firstCbuffer, size_t firstResource)
{
	int cbufferDescriptorOffset = (i * 24);
	int resourceDescriptorOffset = (i * 32);

	Parser->Jump(ChunkOffset, firstCbuffer + cbufferDescriptorOffset);

	uint32_t cbufferNameOffset = Parser->ReadUint32();
	uint32_t variableCount = Parser->ReadUint32();
	uint32_t firstVariableDescriptionOffset = Parser->ReadUint32();
	uint32_t cbufferSize = Parser->ReadUint32();
	uint32_t cbufferFlag = Parser->ReadUint32();
	uint32_t cbufferType = Parser->ReadUint32();

	Parser->Jump(ChunkOffset, cbufferNameOffset);
	std::string cbufferName = Parser->ReadString();


	Parser->Jump(ChunkOffset, firstResource + resourceDescriptorOffset);

	uint32_t resourceBoundName = Parser->ReadUint32();
	uint32_t shaderInputType = Parser->ReadUint32();
	uint32_t resourceReturnType = Parser->ReadUint32();
	uint32_t resourceViewDimension = Parser->ReadUint32();
	uint32_t sampleCount = Parser->ReadUint32();
	uint32_t bindPoint = Parser->ReadUint32();
	uint32_t bindCount = Parser->ReadUint32();
	uint32_t shaderInputFlag = Parser->ReadUint32();

	ConstantBuffer cbuffer = ConstantBuffer(ChunkOffset, firstCbuffer + cbufferDescriptorOffset, cbufferName, bindPoint);


	for (unsigned int j = 0; j < variableCount; j++)
	{
		Parser->Jump(ChunkOffset, firstVariableDescriptionOffset + (j * 24));


		uint32_t variableNameOffset = Parser->ReadUint32();
		uint32_t cbufferOffset = Parser->ReadUint32();

		uint32_t variableSize = Parser->ReadUint32();
		uint32_t variableFlag = Parser->ReadUint32(); // 2 means has been used.

		uint32_t variableTypeOffset = Parser->ReadUint32();
		uint32_t defaultOffset = Parser->ReadUint32();

		size_t readPoint = Parser->GetByteIndex();

		Parser->Jump(ChunkOffset, variableNameOffset);

		std::string variableName = Parser->ReadString();

		Parser->Jump(ChunkOffset, variableTypeOffset);

		uint16_t variableClass = Parser->ReadUint16();
		uint16_t variableType = Parser->ReadUint16();

		uint16_t matrixRowCount = Parser->ReadUint16();
		uint16_t matrixColumnCount = Parser->ReadUint16();
		uint16_t arrayCount = Parser->ReadUint16();
		uint16_t structureMemberCount = Parser->ReadUint16();
		uint16_t firstMemberOffset = Parser->ReadUint16();
		uint16_t unknown16 = Parser->ReadUint16();

		ConstantBuffer::ConstantBufferVariable variable =
			ConstantBuffer::ConstantBufferVariable(variableType, variableClass, variableFlag, variableSize, variableName,
				matrixRowCount, matrixColumnCount, arrayCount, structureMemberCount);

		cbuffer.Variables.push_back(variable);

		if (i != 0)
		{
			Parser->Jump(0, readPoint);
		}
	}

	mConstantBuffers.push_back(cbuffer);
}

void RDEF::ParseResourceBoundDescription(size_t resourceOffset, size_t firstDescription)
{

}
