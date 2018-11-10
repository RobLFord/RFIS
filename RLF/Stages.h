#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <queue>
#include <vector>
#include <cstdint>
#include "InstructionSet.h"

const int MAX_MEM_SIZE = 255;

using namespace std;


namespace customInstruction
{
	class Stages
	{
	public:
		Stages();
		bool start(queue<InstructionSet> intstructions);
		void printBinary(size_t n, size_t bits, bool newLine);
		~Stages();
	private:
		bool theProgramStarted;
		bool theFunctionStarted;
		queue<InstructionSet> theInstructions;
		uint8_t theVariables[MAX_MEM_SIZE];
		uint32_t theRam[MAX_MEM_SIZE];
		bool fetch(InstructionSet instruction);
		bool decode(InstructionSet instruction);
		bool execute(uint32_t x, uint32_t y, InstructionSet instruction);
		bool memory(uint32_t z, InstructionSet instruction);
		bool writeBack(uint32_t z, InstructionSet instruction);
	};
}

