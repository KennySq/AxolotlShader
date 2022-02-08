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
	
	uint16_t shaderType = parser->ReadUint16();
	uint32_t preshaderFlag = parser->ReadUint32();
	uint32_t creatorStringOffset = parser->ReadUint32();

	parser->Jump(sizeof(uint64_t) * 4 * resourceCount);

	std::vector<std::string> cbufferNames(cbufferCount);

	for (unsigned int i = 0; i < cbufferCount; i++)
	{
		
		std::string cbufferName = parser->ReadString();


		cbufferNames[i] = cbufferName;
	}
	parser->OffsetCorrection();

	for (unsigned int i = 0; i < cbufferCount; i++)
	{
		ConstantBuffer cbuffer;

		uint32_t cbufferNameOffset = parser->ReadUint32();
		uint32_t variableCount = parser->ReadUint32();
		uint32_t firstVariableDescriptionOffset = parser->ReadUint32();
		uint32_t cbufferSize = parser->ReadUint32();
		uint32_t cbufferFlag = parser->ReadUint32();
		uint32_t cbufferType = parser->ReadUint32();

		parser->Jump(cbufferNameOffset, firstVariableDescriptionOffset);

		for (unsigned int j = 0; j < variableCount; j++)
		{
			ConstantBuffer::ConstantBufferVariable variable;
			uint32_t variableSize = parser->ReadUint32();
			uint32_t variableNameOffset = parser->ReadUint32();
			uint32_t cbufferOffset = parser->ReadUint32();
			uint32_t variableFlag = parser->ReadUint32();
			uint32_t variableTypeOffset = parser->ReadUint32();
			uint32_t defaultOffset = parser->ReadUint32();

			std::string variableName = parser->ReadString();

			variable.Size = variableSize;
			variable.Name = variableName;
			
			cbuffer.Variables.push_back(variable);
		
			parser->Jump(cbufferNameOffset, variableTypeOffset);
		
			uint16_t variableClass = parser->ReadUint16();
			uint16_t variableType = parser->ReadUint16();

			uint16_t matrixRowCount = parser->ReadUint16();
			uint16_t matrixColumnCount = parser->ReadUint16();
			uint16_t arrayCount = parser->ReadUint16();
			uint16_t structureMemberCount = parser->ReadUint16();
			uint16_t firstMemberOffset = parser->ReadUint16();
		}
		parser->Jump(cbufferNameOffset, firstResourceOffset);

		uint32_t resourceBoundName = parser->ReadUint32();
		uint32_t shaderInputType = parser->ReadUint32();
		uint32_t resourceReturnType = parser->ReadUint32();
		uint32_t resourceViewDimension = parser->ReadUint32();
		uint32_t sampleCount = parser->ReadUint32();
		uint32_t bindPoint = parser->ReadUint32();
		uint32_t bindCount = parser->ReadUint32();
		uint32_t shaderInputFlag = parser->ReadUint32();

		parser->Jump(cbufferNameOffset, creatorStringOffset);
		std::string creator = parser->ReadString();

		cbuffer.Name = cbufferNames[i];
		

		mConstantBuffers.push_back(cbuffer);
	}

}

RDEF::~RDEF()
{
}

void RDEF::ParseResourceBoundDescription(size_t resourceOffset, size_t firstDescription)
{

}
