#pragma once

struct Opcode
{
	Opcode(int opcode)
		: Raw(opcode), Type(opcode & 0xFFF), Size((opcode & 0x7F000000) >> 24), OpcodeSpecific((opcode & 0xFFF000) >> 12), IsExtended(opcode & 0x80000000)
	{

	}

	int Raw;

	int Type;
	int Size;
	int OpcodeSpecific;
	bool IsExtended;
};
