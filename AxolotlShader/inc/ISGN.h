#pragma once
#include"AXParser.h"
#include"BytecodeChunk.h"

#include"ShaderObject.h"
#include"ShaderElement.h"

struct ISGN : public BytecodeChunk
{
	ISGN(const std::shared_ptr<AXParser>& parser);
	~ISGN();
	virtual std::string ToString() const override;

private:
	std::vector<ShaderElement> mInputElements;

	// BytecodeChunk��(��) ���� ��ӵ�
};