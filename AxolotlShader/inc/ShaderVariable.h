#pragma once

struct ShaderVariable
{
	
public:
	ShaderVariable(uint16_t type, uint16_t clss, uint32_t variableFlag, uint32_t variableSize, const std::string& name);

	const std::string& GetName() const { return mName; }
	uint32_t GetVariableFlag() const { return mVariableFlag; }
	uint32_t GetVariableSize() const { return mVariableSize; }
	uint16_t GetVariableType() const { return mType; }
	uint16_t GetVariableClass() const { return mClass; }

private:

	std::string mName;
	uint32_t mVariableFlag;
	uint32_t mVariableSize;

	uint16_t mType;
	uint16_t mClass;
	
};