#pragma once
#include <cstdint>
#include <map>
#include <string>

namespace customInstruction
{
	struct InstructionSet
	{
		uint8_t opCode;
		uint8_t field1;
		uint8_t field2;
		uint32_t field3;
	};

	// Opcodes
	const uint8_t HI = 0x0;
	const uint8_t BYE = 0x1;
	const uint8_t BEGIN = 0x2;
	const uint8_t END = 0x3;
	const uint8_t SET = 0x4;
	const uint8_t LOAD = 0x5;
	const uint8_t STORE = 0x6;
	const uint8_t ADD = 0x7;

	const std::map<std::string, uint8_t> MAPPED_OPCODES =
	{
		{ "hi", HI },
		{ "bye", BYE },
		{ "begin", BEGIN },
		{ "end", END },
		{ "set", SET },
		{ "load", LOAD },
		{ "store", STORE },
		{ "+", ADD },
	};
}