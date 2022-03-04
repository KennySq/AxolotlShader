#include"pch.h"
#include"OSGN.h"

OSGN::OSGN(const std::shared_ptr<AXParser>& parser)
	: BytecodeChunk(parser->GetByteIndex(), parser)
{
	uint32_t chunkSize = parser->ReadUint32();
	ChunkOffset = parser->GetByteIndex();
	uint32_t elementCount = parser->ReadUint32();
	uint32_t unknownData0 = parser->ReadUint32();

	for (int i = 0; i < elementCount; i++)
	{
		uint32_t offsetToFirstElementName = parser->ReadUint32();
		uint32_t semanticIndex = parser->ReadUint32();
		uint32_t systemValueType = parser->ReadUint32();
		uint32_t componentType = parser->ReadUint32();
		uint32_t registerIndex = parser->ReadUint32();
		uint8_t mask = parser->ReadUint8();
		uint8_t readWriteMask = parser->ReadUint8();

		size_t readBack = parser->GetByteIndex();

		parser->Jump(ChunkOffset, offsetToFirstElementName);

		std::string elementName = parser->ReadString();

		parser->Jump(0, readBack);
		parser->OffsetCorrection();

		int componentCount = mask;

		mInputElements.emplace_back(elementName, componentCount, registerIndex, systemValueType);

	}

	parser->Jump(ChunkOffset, chunkSize);
}

OSGN::~OSGN()
{
}

std::string OSGN::ToString() const
{
	std::string buffer = "OSGN\n";
	size_t elementCount = mInputElements.size();
	for (int i = 0; i < elementCount; i++)
	{
		buffer += "\t" + mInputElements[i].Name + "\n";
		buffer += "\t - Component Mask : " + std::to_string(mInputElements[i].ComponentMask) + "\n";
		buffer += "\t - Register Index : " + std::to_string(mInputElements[i].Register) + "\n";
	}

	return buffer;
}
