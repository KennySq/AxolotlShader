#pragma once
#include"AXParser.h"
#include"BytecodeChunk.h"

#include"ShaderObject.h"

struct ISGN : public BytecodeChunk
{
	ISGN(std::shared_ptr<AXParser> parser);
	~ISGN();
};