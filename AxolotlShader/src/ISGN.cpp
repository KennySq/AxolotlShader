#include"pch.h"
#include"ISGN.h"

ISGN::ISGN(std::shared_ptr<AXParser> parser)
	: BytecodeChunk(parser->GetByteIndex(), parser)
{
	uint32_t someData = parser->ReadUint32();



}

ISGN::~ISGN()
{
}
