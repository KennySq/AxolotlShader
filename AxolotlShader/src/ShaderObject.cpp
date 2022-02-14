#include"pch.h"
#include"ShaderObject.h"

ShaderObject::ShaderObject(size_t parent, size_t offset, const std::string& name, uint32_t type)
	: mName(name), mParent(parent), mOffset(offset), Type(type)
{
}
