#pragma once

struct ShaderElement
{
	ShaderElement(const std::string& name, int componentMask, int registr, int systemValue)
		: Name(name), ComponentMask(componentMask), Register(registr), SystemValue(systemValue)
	{

	}

	std::string Name;
	int ComponentMask;
	int Register;
	int SystemValue;
};