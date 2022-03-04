#include"pch.h"
#include"SHDR.h"

SHDR::SHDR(const std::shared_ptr<AXParser>& parser)
	: BytecodeChunk(parser->GetByteIndex(), parser)
{
	uint32_t chunkSize = parser->ReadUint32();
	uint8_t shaderModel = parser->ReadUint8();
	
	uint8_t minor = (shaderModel & 0xF0) >> 4;
	uint8_t major = shaderModel & 0xF;

	uint8_t offset0 = parser->ReadUint8();

	uint16_t programType = parser->ReadUint16();
	uint32_t dwordCount = parser->ReadUint32();

	Opcode opcode0 = parser->ReadUint32();


}

SHDR::~SHDR()
{
}

std::string SHDR::ToString() const
{
	std::string buffer = "SHDR\n";
	return buffer;
}
