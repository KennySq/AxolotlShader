#pragma once
struct ShaderObject
{
public:
	ShaderObject(size_t parent, size_t offset, const std::string& name);

private:
	size_t mParent;
	size_t mOffset;
	
	std::string mName;

	// type?

};