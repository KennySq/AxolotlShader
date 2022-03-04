#pragma once
#include"BytecodeChunk.h"
#include"Opcode.h"

struct SHDR : public BytecodeChunk
{
public:
	SHDR(const std::shared_ptr<AXParser>& parser);
	~SHDR();

	virtual std::string ToString() const override;

private:


	
};
