#include<pch.h>
#include"Decoder.h"

uint32_t Decoder::MakeMask(uint8_t start, uint8_t end)
{
	uint32_t mask = 0;

	for (unsigned int i = start; i <= end; i++)
	{
		mask |= (uint32_t) 1 << i;
	}

	return mask;
}

uint32_t Decoder::Decode(uint32_t token, uint8_t start, uint8_t end)
{
	const uint32_t mask = MakeMask(start, end);
	const uint8_t shift = start;

	return (token & mask) >> shift;
}

std::string Decoder::ToFourString(uint32_t fourStr)
{
	char str[5];

	str[0] = Decode<char>(fourStr, 0, 7);
	str[1] = Decode<char>(fourStr, 8, 15);
	str[2] = Decode<char>(fourStr, 16, 23);
	str[3] = Decode<char>(fourStr, 24, 31);
	str[4] = '\0';
	return std::string(str);
}
