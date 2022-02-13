#include"pch.h"
#include"ShaderObject.h"

ShaderObject::ShaderObject(size_t parent, size_t offset, const std::string& name)
	: mName(name), mParent(parent), mOffset(offset)
{
}
