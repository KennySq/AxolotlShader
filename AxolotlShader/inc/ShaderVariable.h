#pragma once

struct ShaderVariable
{
	
public:
	ShaderVariable(uint32_t variableFlag, uint32_t variableSize, const std::string& name);
private:

	std::string mName;
	uint32_t mVariableFlag;
	uint32_t mVariableSize;
	
};