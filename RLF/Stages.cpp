#include "Stages.h"

using namespace std;

namespace customInstruction
{
	Stages::Stages()
	{
		theProgramStarted = false;
		theFunctionStarted = false;
	}

	bool Stages::start(queue<InstructionSet> intstructions)
	{
		cout << "\n\n------- Processing Instructions ------" << endl;
		InstructionSet instruction = {};
		size_t instructionSetSize = intstructions.size();
		for (size_t i = 0; i < instructionSetSize; i++)
		{
			instruction = intstructions.front();
			if (!fetch(instruction))
			{
				intstructions.pop();
				if (intstructions.size() != 0)
				{
					cout << "----- next instruction ----" << endl;
				}
			}
			else
			{
				cout << __func__ << " Error: with instruction (" << i+1 <<")" << endl;
				return false;
			}
		}
		return true;
	}

	Stages::~Stages()
	{
	}
	bool Stages::fetch(InstructionSet instruction)
	{
		cout << __func__ << endl;
		bool error = false;
		switch (instruction.opCode)
		{
		case HI:
			cout << "Start of Program" << endl;
			std::fill_n(theRam, MAX_MEM_SIZE, 0);
			theProgramStarted = true;
			break;
		case BYE:
			cout << "End of Program" << endl;
			std::fill_n(theRam, MAX_MEM_SIZE, 0);
			theProgramStarted = false;
			break;
		case BEGIN:
			//cout << "Start of new function" << endl;
			theFunctionStarted = true;
			break;
		case END:
			//cout << "End of new function" << endl;
			theFunctionStarted = false;
			break;
		case LOAD:
			printf("Loading %d from RAM to var %d\n", theRam[instruction.field1], instruction.field1);
			theVariables[instruction.field1] = theRam[instruction.field1];
			return decode(instruction);
		default:
			if (theProgramStarted && theFunctionStarted)
			{
				return decode(instruction);
			}
			else if (!theProgramStarted)
			{
				printf("Error: Need to start Program\n");
			}
			else if (!theFunctionStarted)
			{
				printf("Error: Need to start Function\n");
			}
			else
			{
				printf("Error: Invalid Instruction (%d)\n", instruction.opCode);
				error = true;
			}
			break;
		}

		return error;
	}
	bool Stages::decode(InstructionSet instruction)
	{
		cout << __func__ << endl;
		switch (instruction.opCode)
		{
		case ADD:
			return execute(theVariables[instruction.field2], theVariables[instruction.field3], instruction);
		default:
			return execute(0, 0, instruction);
		}
		return false;
	}
	bool Stages::execute(uint32_t x, uint32_t y, InstructionSet instruction)
	{
		uint32_t z = 0;
		cout << __func__ << endl;
		switch (instruction.opCode)
		{
		case ADD:
			z = x + y;
			printf("%d = %d + %d\n", z, x, y);
			return(memory(z, instruction));
		default:
			return memory(0, instruction);
		}
		return false;
	}
	bool Stages::memory(uint32_t z, InstructionSet instruction)
	{
		cout << __func__ << endl;
		switch (instruction.opCode)
		{

		case SET:
			return(writeBack(0, instruction));
		case STORE:
			theRam[instruction.field1] = theVariables[instruction.field1];
			return false;
		case ADD:
			return(writeBack(z, instruction));
		}
		return false;
	}
	bool Stages::writeBack(uint32_t z, InstructionSet instruction)
	{
		cout << __func__ << endl;
		switch (instruction.opCode)
		{
		case SET:
			theVariables[instruction.field1] = instruction.field3;
			return false;
		case ADD:
			theVariables[instruction.field1] = z;
			return false;
		}
		return false;
	}

	void Stages::printBinary(size_t n, size_t bits, bool newLine)
	{
		size_t i;
		for (i = 1 << bits - 1; i > 0; i = i / 2)
		{
			(n & i) ? printf("1") : printf("0");
		}
		if (newLine)
		{
			printf("\n");
		}
		else
		{
			printf("   ");
		}
	}
}
