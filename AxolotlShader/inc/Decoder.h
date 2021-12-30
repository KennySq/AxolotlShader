#pragma once

struct Decoder
{
public:
	static uint32_t MakeMask(uint8_t start, uint8_t end);
	static uint32_t Decode(uint32_t token, uint8_t start, uint8_t end);

	template<typename _Ty>
	static _Ty Decode(uint32_t token, uint8_t start, uint8_t end)
	{
		return (_Ty)Decode(token, start, end);
	}

	static std::string ToFourString(uint32_t fourStr);
};