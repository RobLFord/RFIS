#include <iostream>
#include <string>
#include "RFIS.h"

using namespace std;
using namespace customInstruction;

int main(int argc, char *argv[])
{
	if (argc > 1)
	{
		string fileName = argv[1];
		cout << "Going to run RFIS program " << fileName << endl;

		RFIS theRFIS(fileName);
		if (theRFIS.compile())
		{
			theRFIS.run();
		};
	}

	system("pause");
	return 0;
}