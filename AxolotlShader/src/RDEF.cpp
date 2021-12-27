#include<pch.h>
#include"RDEF.h"

RDEF::RDEF()
{
}

RDEF::~RDEF()
{
}

void RDEF::Parse(size_t start, size_t end, std::shared_ptr<AXParser>&& parser)
{
	AXParser::ByteBlock chunkBuffer = parser->Read(start, end);

	

}
