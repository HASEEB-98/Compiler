#include "machineCodeGenerator.h"

class VM {
public:
	machineCodeGenerator* _machineCodeGnerator;
    unordered_map <int, pair<string, string>> ds;
	int ** mc;
	
	VM(machineCodeGenerator* _machineCodeGnerator);
    void createDS();
	void createMC();
    char readChar(int address);	
    void saveChar(int address, char value);
	int readInt(int address);
	void saveInt(int address, int value);
	string readString(int address);
	void run();

	
};
