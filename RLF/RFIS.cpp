#include "RFIS.h"


namespace customInstruction
{
	RFIS::RFIS(const string &filename) :
		theFileName(filename)
	{
	}

	bool RFIS::compile()
	{
		ifstream file;
		file.open(theFileName, std::ifstream::binary);

		if (!file) {
			cout << "Cannot open input file.\n";
			return false;
		}

		char fileStrLine[1024];

		cout << " ---------- Compiled Instructions ----------- \n"<< endl;
		while (file)
		{
			file.getline(fileStrLine, 1024);
			if (file)
			{
				//debug
				//cout << fileStrLine << endl;

				//tokening the each line
				char seps[] = " ";
				char *token = NULL;
				char *next_token = NULL;

				// Establish string and get the first token:  
				token = strtok_s(fileStrLine, seps, &next_token);

				size_t fieldNum = 0;
				InstructionSet instructionSet = {};
				// While there are tokens string
				while ((token != NULL))
				{
					// Get next token:  
					if (token != NULL)
					{
						//printf(" %s\n", token);
						//building the instructions here from ascii
						buildInstuction(fieldNum, token, &instructionSet);

						token = strtok_s(NULL, seps, &next_token);
						fieldNum++;
					}
				}
				theInstructions.emplace(instructionSet);
				cout << endl;
			}
		}

		file.close();
		return true;
	}

	void RFIS::buildInstuction(size_t fieldNum, string tokenField, InstructionSet *instructionSet)
	{
		std::map<std::string, uint8_t> mappedOpCodes = MAPPED_OPCODES;
		std::map<std::string, uint8_t>::iterator it;

		//removing any spaces and returns
		tokenField.erase(std::remove(tokenField.begin(), tokenField.end(), ' '), tokenField.end());
		tokenField.erase(std::remove(tokenField.begin(), tokenField.end(), '\r'), tokenField.end());
		
		//cout << tokenField << endl;

		std::string::size_type sz;   // alias of size_t

		switch (fieldNum)
		{
		case 0:
			it = mappedOpCodes.find(tokenField);
			if (it != mappedOpCodes.end())
			{
				//std::cout << "storing Opcode instruction" << '\n';
				instructionSet->opCode = it->second;
				theStages.printBinary(instructionSet->opCode, 8, false);
				
			}
			else
			{
				std::cout << "Error: Cannot find Opcode instruction " << "(" << tokenField << ")"  << '\n';
			}
			break;
		case 1:
			instructionSet->field1 = std::stoi(tokenField, &sz);
			theStages.printBinary(instructionSet->field1, 8, false);
			break;
		case 2:
			instructionSet->field2 = std::stoi(tokenField, &sz);
			theStages.printBinary(instructionSet->field2, 8, false);
			break;
		case 3:
			instructionSet->field3 = std::stoi(tokenField, &sz);
			theStages.printBinary(instructionSet->field3, 32, true);
			break;
		}
	}

	void RFIS::run()
	{
		theStages.start(theInstructions);
	}

	RFIS::~RFIS()
	{
	}
}

