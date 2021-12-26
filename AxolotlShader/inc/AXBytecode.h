#pragma once
#include"RDEF.h"

struct AXBytecode
{
public:
	AXBytecode(const char* path);
	~AXBytecode();


private:
	std::unique_ptr<RDEF> mRDEF;

	std::shared_ptr<AXParser> mParser;

};