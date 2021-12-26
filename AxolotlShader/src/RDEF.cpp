#include<pch.h>
#include"RDEF.h"

void RDEF::Parse(size_t start, size_t end, std::unique_ptr<AXParser>&& parser)
{
	std::string chunkBuffer = parser->Read(start, end);

	

}
