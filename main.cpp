#include <iostream>
#include "VM.h"

using namespace std;

int main(int argc, char* argv[])
{
	//asking for file name as command line arguments
	if (argc == 2)
	{
		parser _parser(argv[1]);
		_parser.parserMain();

		machineCodeGenerator _mcg("tac.txt", "symbol_table.txt", "mc.txt");
		_mcg.generateTACToMachineCode();

		VM _vm(& _mcg);
		_vm.run();
	}
	else if (argc > 2)
	{ //argument limit exceeds
		cout << "Too many arguments" << endl;
	}
	else //if file name is'nt given
	{
		cout << "Please provide a file name" << endl;
	}
	return 0;
}
