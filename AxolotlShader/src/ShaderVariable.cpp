#include"pch.h"
#include"ShaderVariable.h"

ShaderVariable::ShaderVariable(uint32_t variableFlag, uint32_t variableSize, const std::string& name)
	: mVariableFlag(variableFlag), mVariableSize(variableSize), mName(name)
{
}
