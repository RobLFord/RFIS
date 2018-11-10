#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <queue>
#include <cstdio> 
#include <algorithm>
#include "Stages.h"
#include "InstructionSet.h"

using namespace std;

namespace customInstruction
{
	class RFIS
	{
	public:
		RFIS(const string &filename);
		bool compile();
		void buildInstuction(size_t fieldNum, string tokenField, InstructionSet *instructionSet);
		void run();
		~RFIS();
	private:
		string theFileName;
		queue<InstructionSet> theInstructions;
		Stages theStages;
	};
};


