#include "machineCodeGenerator.h"

string machineCodeGenerator::newTemp(){
	return "z" + to_string(temp_count++); 
}

machineCodeGenerator::machineCodeGenerator(string TACFileName, string symbolTableFileName, string machineCodeFileName){
	initializeOpCodeTable();
	createSymboleTable(symbolTableFileName);
	temp_count = 0;
	int negativeInfinity = -99999999;

	//get no of lines in TAC
	finTAC.open(TACFileName);
	if(!finTAC){
		exit(1);
	}
	int lines = 0; 
	string line;
	while (getline(finTAC, line))
		lines++;
	totalLines = lines;
	mc = new int* [lines + 1];
	finTAC.close();

	finTAC.open(TACFileName);
	foutMC.open(machineCodeFileName);
}

vector<string> machineCodeGenerator::split(string TAC){
	vector <string> tokens;
	
	stringstream check1(TAC);
	
	string intermediate;
	
	while(getline(check1, intermediate, ' '))
	{
		tokens.push_back(intermediate);
		if(intermediate == "out"){
			string temp = "";
			getline(check1, intermediate, ' ');
			if(intermediate[0] == '"'){
				temp += intermediate + " ";
				while(getline(check1, intermediate, ' ')){
					temp += intermediate + " ";
				}
			}
			else{
				temp += intermediate;
			}
			tokens.push_back(temp);
		}
	}

	return tokens;
}

char* machineCodeGenerator::getSymbolAdress(string symbol) {
	pair<string, string> temp;
	pair<string, pair<string, string>> temp1;


	if(symbol[0] >= '0' && symbol[0] <= '9'){
		currentAddress += 4;
		temp.first = to_string(currentAddress);
		temp.second = symbol;
		temp1.first = "INT";
		temp1.second = temp;
		symbolTable[newTemp()] = temp1;
		return (char*)temp.first.c_str();
	}
	else if(symbol[0] == '\''){
		currentAddress += 1;
		temp.first = to_string(currentAddress);
		temp.second = symbol;
		temp1.first = "CHAR";
		temp1.second = temp;
		symbolTable[newTemp()] = temp1;
		return (char*)temp.first.c_str();
	}
	else if(symbol[0] == '\"'){
		currentAddress += 1;
		temp.first = to_string(currentAddress);
		temp.second = symbol;
		temp1.first = "STRING";
		temp1.second = temp;
		symbolTable[newTemp()] = temp1;
		return (char*)temp.first.c_str();
	}
	else if (symbolTable.find(symbol) == symbolTable.end()) {
		cout << "Variable: |" << symbol << "| is not declared!";
		exit(1);
	}
	
	return (char*)symbolTable[symbol].second.first.c_str();
}

void machineCodeGenerator::addToMemArrayAndFile(vector<int>data) {
	mc[lineNo] = new int[4];
	for (int i = 0; i < data.size(); i++) {
		mc[lineNo][i] = int(data[i]);
		foutMC << data[i];
		if (i != data.size() - 1) {
			foutMC << " ";
		}
		else {
			foutMC << endl;
		}
	}
	if (data.size() < 4) {
		for (int i = data.size(); i < 4; i++) {
			mc[lineNo][i] = negativeInfinity;
		}
	}
	lineNo++;
}

bool machineCodeGenerator::isAssignment(vector<string>tokens) {
	if (tokens.size() == 3 && tokens[1] == "=") {
		vector<int>data;
		data.push_back(opCodeTable["="]);
		data.push_back(atoi(getSymbolAdress(tokens[2])));
		data.push_back(atoi(getSymbolAdress(tokens[0])));
		addToMemArrayAndFile(data);
	}
	return false;
}

bool machineCodeGenerator::isOutput(vector<string>tokens) {
	if (tokens.size() == 2 && tokens[0] == "out") {
		vector<int>data;
		data.push_back(opCodeTable["OUT"]);
		data.push_back(atoi(getSymbolAdress(tokens[1])));
		addToMemArrayAndFile(data);
	}
	return false;
}

bool machineCodeGenerator::isInput(vector<string>tokens) {
	if (tokens.size() == 2 && tokens[0] == "in") {
		vector<int>data;
		if (symbolTable[tokens[1]].first == "INT") {
			data.push_back(opCodeTable["INI"]);
		}
		else if (symbolTable[tokens[1]].first == "CHAR") {
			data.push_back(opCodeTable["INC"]);
		}
		data.push_back(atoi(getSymbolAdress(tokens[1])));
		addToMemArrayAndFile(data);
	}
	return false;
}

bool machineCodeGenerator::isIf(vector<string>tokens) {
	if (tokens.size() == 6 && tokens[0] == "if") {
		vector<int>data;
		data.push_back(opCodeTable[tokens[2]]);
		data.push_back(atoi(getSymbolAdress(tokens[1])));
		data.push_back(atoi(getSymbolAdress(tokens[3])));
		data.push_back(atoi((char*)tokens[5].c_str()));
		addToMemArrayAndFile(data);
	}
	return false;
}

bool machineCodeGenerator::isGoto(vector<string>tokens) {
	if (tokens.size() == 2 && tokens[0] == "goto") {
		vector<int>data;
		data.push_back(opCodeTable["goto"]);
		data.push_back(atoi((char*)tokens[1].c_str()));
		addToMemArrayAndFile(data);
	}
	return false;
}

bool machineCodeGenerator::isArithmetic(vector<string>tokens) {
	if (tokens.size() == 5 && tokens[1] == "=") {
		vector<int>data;
		data.push_back(opCodeTable[tokens[3]]);
		data.push_back(atoi(getSymbolAdress(tokens[2])));
		data.push_back(atoi(getSymbolAdress(tokens[4])));
		data.push_back(atoi(getSymbolAdress(tokens[0])));
		addToMemArrayAndFile(data);
	}
	return false;
}

bool machineCodeGenerator::isReturn(vector<string>tokens) {
	if (tokens.size() == 2 && tokens[0] == "ret") {
		pair<string, string> temp;
		pair<string, pair<string, string>> temp1;
		
		vector<int>data;
		data.push_back(opCodeTable["ret"]);
		data.push_back(atoi(getSymbolAdress(tokens[1])));
		addToMemArrayAndFile(data);
	}
	return false;
}

void machineCodeGenerator::parse(string TAC){
	vector<string> tokens = split(TAC);
	


	// for(int i = 0; i < tokens.size(); i++){
	// 	pair<string, string> temp;
	// 	pair<string, pair<string, string>> temp1;
	// 	if(tokens[i][0] >= '0' && tokens[i][0] <= '9'){
	// 		temp.first = to_string(currentAddress);
	// 		currentAddress += 4;
	// 		temp.second = tokens[1];
	// 		temp1.first = "INT";
	// 		temp1.second = temp;
	// 		symbolTable[newTemp()] = temp1;
	// 	}
	// 	else if(tokens[i][0] == '\''){
	// 		temp.first = to_string(currentAddress);
	// 		currentAddress += 1;
	// 		temp.second = tokens[1];
	// 		temp1.first = "CHAR";
	// 		temp1.second = temp;
	// 		symbolTable[newTemp()] = temp1;
	// 	}
	// 	else if(tokens[i][0] == '\"'){
	// 		temp.first = to_string(currentAddress);
	// 		currentAddress += 1;
	// 		temp.second = tokens[1];
	// 		temp1.first = "STRING";
	// 		temp1.second = temp;
	// 		symbolTable[newTemp()] = temp1;
	// 	}
	// 	else if((tokens[i][0] >= 'a' && tokens[i][0] <= 'z') || (tokens[i][0] >= 'A' && tokens[i][0] <= 'Z')){
	// 	}
	// }
	// cout << endl;

	

	if (!isAssignment(tokens))
		if (!isOutput(tokens))
			if (!isInput(tokens))
				if (!isIf(tokens))
					if (!isGoto(tokens))
						if (!isReturn(tokens))
							if (!isArithmetic(tokens))
								return;
}

void machineCodeGenerator::generateTACToMachineCode(){
	string TAC;
	while (getline(finTAC, TAC)) {
		parse(TAC);
	}

	// for (auto i : symbolTable)
    //     cout << i.first << "   " << i.second.first << "   " << i.second.second.first << "   " << i.second.second.second << endl;
	finTAC.close();
	foutMC.close();

	
}

void machineCodeGenerator::initializeOpCodeTable() {
	opCodeTable["=="] = 0;
	opCodeTable["<="] = 1;
	opCodeTable[">="] = 2;
	opCodeTable["!="] = 3;
	opCodeTable[">"] = 4;
	opCodeTable["<"] = 5;
	opCodeTable["="] = 6;
	opCodeTable["+"] = 7;
	opCodeTable["-"] = 8;
	opCodeTable["/"] = 9;
	opCodeTable["*"] = 10;
	opCodeTable["%"] = 11;
	opCodeTable["goto"] = 12;
	opCodeTable["INI"] = 13;
	opCodeTable["INC"] = 14;
	opCodeTable["OUT"] = 15;
	opCodeTable["ret"] = 16;
}

void machineCodeGenerator::createSymboleTable(string fileName){
	ifstream fin;

	fin.open(fileName);
	if(fin){
		string type, name;
		int address;
		
		while(fin >> type >> name >> address){
			
			pair<string, string> temp;
			pair<string, pair<string, string>> temp1;
			temp.first = to_string(address);
			temp.second = "Null";
			temp1.first = type;
			temp1.second = temp;
			symbolTable[name] = temp1;
			currentAddress = address;
		}
	}
}

