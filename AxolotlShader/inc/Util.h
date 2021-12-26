#pragma once

#include"pch.h"
#define EOL 0x00


inline unsigned int GetLength(const char* target)
{
	unsigned int i = 0;
	while (target[i] != EOL)
	{
		i++;
	}

	return i;
}

inline bool Contains(const std::string& container, const char* target)
{
	unsigned int targetLength = GetLength(target);

	for (size_t i = 0; i < container.size(); i++)
	{
		unsigned int match = 0;

		for (size_t j = 0; j < targetLength; j++)
		{
			if (i + j < container.size())
			{
				if (container[i + j] != target[j])
				{
					continue;
				}

				match++;
			}
		}

		if (match == targetLength)
		{
			return true;
		}

	}

	return false;
}