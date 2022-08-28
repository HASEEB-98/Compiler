#include "parser.h"

class machineCodeGenerator
{
    
public:

	unordered_map<string, pair<string, pair<string, string>>> symbolTable;
	unordered_map<string, int> opCodeTable;
	int** mc;
	int totalLines;
	int lineNo;
	int temp_count;
	int negativeInfinity;
	ifstream finTAC;
	ofstream foutMC;
	int currentAddress;

	string newTemp();

    machineCodeGenerator(string TACFileName, string symbolTableFileName, string machineCodeFileName);

	vector<string> split(string TAC);

	char* getSymbolAdress(string symbol);
	
	void addToMemArrayAndFile(vector<int>data);

	bool isAssignment(vector<string>tokens);
		
	bool isOutput(vector<string>tokens);
	
	bool isInput(vector<string>tokens);
	
	bool isIf(vector<string>tokens);
	
	bool isGoto(vector<string>tokens);
		
	bool isArithmetic(vector<string>tokens);
	
	bool isReturn(vector<string>tokens);

	void parse(string TAC);

	void generateTACToMachineCode();

    void initializeOpCodeTable();

    void createSymboleTable(string fileName);
    

};