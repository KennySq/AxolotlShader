#pragma once
struct ShaderObject
{
public:
	ShaderObject(size_t parent, size_t offset, const std::string& name, uint32_t type);

	const uint32_t Type;

private:
	size_t mParent;
	size_t mOffset;
	
	std::string mName;
};