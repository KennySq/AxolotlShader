#pragma once
#include"BytecodeChunk.h"
#include"ShaderElement.h"

struct OSGN : public BytecodeChunk
{
public:
	OSGN(const std::shared_ptr<AXParser>& parser);
	~OSGN();

	virtual std::string ToString() const override;
private:
	std::vector<ShaderElement> mInputElements;

};