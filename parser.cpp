#include "parser.h"

string parser::newTemp(){
	return "t" + to_string(temp_count++); 
}

void parser::syntax_error()
{
	cout << "SYNTAX ERROR\n";
	exit(1);
}

token parser::expect(TokenType expected_type)
{
	token t = _lexer.getNextToken();
	if (t.tokenType != expected_type)
		syntax_error();
	return t;
}

parser::parser(const char filename[])
{
	_lexer = lexer(filename);
	fout_symbol_table.open("symbol_table.txt");
	fout_TAC.open("tac.txt");
	line_num = 1;
	temp_count = 0;
	TAC = "";
	currentAddress = 0;
}

void parser::readAndPrintAllInput() // read and print allinputs (provided)
{
	token t;
	t = _lexer.getNextToken();
	while (t.tokenType != TokenType::END_OF_FILE)
	{
		t.Print();
		t = _lexer.getNextToken();
	}
}

void parser::resetPointer()
{
	_lexer.resetPointer();
}

string parser::E()
{
	string exp = "";
	exp += T();
	exp += R();
	return exp;
}

string parser::R()
{
	string exp = "";
	if (_lexer.peek(1).tokenType == TokenType::ADD_OP)
	{
		expect(TokenType::ADD_OP);
		exp += " + ";
		exp += T();
		exp += R();
	}
	else if (_lexer.peek(1).tokenType == TokenType::SUBTRACT_OP)
	{
		expect(TokenType::SUBTRACT_OP);
		exp += " - ";
		exp += T();
		exp += R();
	}
	else
	{
		
	}
	return exp;
}

string parser::T()
{
	string exp = "";
	exp += F();
	exp += rPrime();
	return exp;
}

string parser::F()
{
	if (_lexer.peek(1).tokenType == TokenType::ID)
	{
		string id = _lexer.peek(1).lexeme;
		expect(TokenType::ID);
		return id;
	}
	else if (_lexer.peek(1).tokenType == TokenType::NUMBER)
	{
		string id = _lexer.peek(1).lexeme;
		expect(TokenType::NUMBER);
		return id;
	}
	else
	{
		cout << "Error-Bad Token" << endl;
		exit(1);
	}
}

string parser::rPrime()
{
	string exp = "";
	if (_lexer.peek(1).tokenType == TokenType::MULTIPLY_OP)
	{
		expect(TokenType::MULTIPLY_OP);
		exp += " * ";
		exp += F();
	}
	else if (_lexer.peek(1).tokenType == TokenType::DIVIDE_OP)
	{
		expect(TokenType::DIVIDE_OP);
		exp += " / ";
		exp += F();
	}
	else if (_lexer.peek(1).tokenType == TokenType::MOD_OP)
	{
		expect(TokenType::MOD_OP);
		exp += " % ";
		exp += F();
	}
	else
	{
	}
	return exp;
}

string parser::assign()
{
	string assign = "";
	assign += _lexer.peek(1).lexeme;
	expect(TokenType::ID);
	assign += " = ";
	expect(TokenType::ASSIGN);
	assign += E();
	if(_lexer.peek(1).tokenType == TokenType::SEMI_COLON){
		expect(TokenType::SEMI_COLON);
		assign += ";";
	}
	
	return assign;
}

void parser::init()
{
	string initialization = _lexer.peek(1).lexeme;
	expect(TokenType::ID);
	initialization += X();
	fout_TAC << initialization << endl;
}

string parser::X()
{
	string exp = "";
	if (_lexer.peek(1).tokenType == TokenType::ASSIGN)
	{
		exp += " = ";
		expect(TokenType::ASSIGN);
		exp += E();
		expect(TokenType::SEMI_COLON);
	}
	else if (_lexer.peek(1).tokenType == TokenType::INT)
	{
		expect(TokenType::INT);
		expect(TokenType::SEMI_COLON);
	}
	else if (_lexer.peek(1).tokenType == TokenType::CHAR)
	{
		expect(TokenType::CHAR);
		expect(TokenType::SEMI_COLON);
	}
	else
	{
	}
	return exp;
}

string parser::print()
{
	string output = "out ";
	if (_lexer.peek(1).tokenType == TokenType::PRINT)
	{
		expect(TokenType::PRINT);
		output += pst();
		expect(TokenType::SEMI_COLON);
		
	}
	return output;
}

string parser::pst()
{
	if (_lexer.peek(1).tokenType == TokenType::STRING)
	{
		string str = _lexer.peek(1).lexeme;
		expect(TokenType::STRING);
		return str;
	}
	else
	{
		return E();
	}
}

string parser::condition()
{
	string cond = "";
	cond += E();
	cond += " ";
	cond += ro();
	cond += " ";
	cond += E();
	return cond;
}

string parser::ro()
{
	if (_lexer.peek(1).tokenType == TokenType::RELATION_OP)
	{
		string ro = _lexer.peek(1).lexeme;
		expect(TokenType::RELATION_OP);
		if(ro == "="){
			return "==";
		}
		return ro;
	}
	else
	{
		cout << "SYNTAX ERROR\n";
		exit(1);
		return "";
	}
}

string parser::_return()
{
	string ret = "ret ";
	expect(TokenType::RETURN);
	ret += E();
	expect(TokenType::SEMI_COLON);
	return ret;
}

string parser::input()
{
	string in = "in ";
	expect(TokenType::IN);
	in += _lexer.peek(1).lexeme;
	expect(TokenType::ID);
	expect(TokenType::SEMI_COLON);

	return in;
}

void parser::_for()
{
	expect(TokenType::FOR);

	//TAC  += to_string(line_num) + " ";
	TAC += assign();
	TAC += "\n";
	line_num++;
	
	expect(TokenType::COMMA);

	int curr_line = line_num;

	//TAC  += to_string(line_num) + " ";
	TAC += "if ";
	TAC += condition();
	TAC += " goto " + to_string(line_num + 2) + "\n";
	line_num++;
	
	//TAC += to_string(line_num) + " goto ";
	TAC += "goto ";
	line_num++;

	expect(TokenType::COMMA);

	string temp1 = TAC;
	TAC = "";

	string temp2 = assign();
	
	expect(TokenType::COLON);
	expect(TokenType::BEGIN);
	code();
	expect(TokenType::END);

	temp1 += to_string(line_num + 2);
	temp1 += "\n";

	TAC = temp1 + TAC;
	
	//TAC += to_string(line_num) + " " + temp2 + "\n";
	TAC += temp2 + "\n";
	line_num++;

	//TAC += to_string(line_num) + " goto " + to_string(curr_line) + "\n";
	TAC += "goto " + to_string(curr_line) + "\n";
}

void parser::_if()
{
	expect(TokenType::IF);	

	//TAC += to_string(line_num) + " if ";
	TAC += "if ";
	TAC += condition();
	TAC += " goto " + to_string(line_num + 2) + "\n";
	line_num++;
	
	//TAC += to_string(line_num) + " goto ";
	TAC += "goto ";
	line_num++;

	string temp = TAC;
	TAC = "";

	expect(TokenType::COLON);
	expect(TokenType::BEGIN);
	code();
	expect(TokenType::END);

	temp += to_string(line_num + 1);
	temp += "\n";

	TAC = temp + TAC;
	
	if (_lexer.peek(1).tokenType == TokenType::ELIF || _lexer.peek(1).tokenType == TokenType::ELSE)
	{	
		temp = TAC;
		TAC = "";
		int curr_line = line_num;
		line_num++;
		next();	
		//temp += to_string(curr_line) + " goto " + to_string(line_num) + "\n";
		temp += "goto " + to_string(line_num) + "\n";
		TAC = temp + TAC;
	}
}

void parser::_elseif()
{
	if (_lexer.peek(1).tokenType == TokenType::ELIF)
	{
			
		expect(TokenType::ELIF);	

		//TAC += to_string(line_num) + " if ";
		TAC += "if ";		TAC += condition();
		TAC += " goto " + to_string(line_num + 2) + "\n";
		line_num++;
		
		//TAC += to_string(line_num) + " goto ";
		TAC += "goto ";
		line_num++;

		string temp = TAC;
		TAC = "";

		expect(TokenType::COLON);
		expect(TokenType::BEGIN);
		code();
		expect(TokenType::END);

		temp += to_string(line_num + 1);
		temp += "\n";

		TAC = temp + TAC;

		if (_lexer.peek(1).tokenType == TokenType::ELIF || _lexer.peek(1).tokenType == TokenType::ELSE)
		{	
			temp = TAC;
			TAC = "";
			int curr_line = line_num;
			line_num++;
			next();	
			//temp += to_string(curr_line) + " goto " + to_string(line_num) + "\n";
			temp += "goto " + to_string(line_num) + "\n";
			TAC = temp + TAC;
		}
	}
	else
	{
		// DO NOTHING
	}
}

void parser::_else()
{
	if (_lexer.peek(1).tokenType == TokenType::ELSE)
	{
		expect(TokenType::ELSE);
		expect(TokenType::COLON);
		expect(TokenType::BEGIN);
		code();
		expect(TokenType::END);
	}
	else
	{
		// DO NOTHING
	}
}

void parser::next()
{
	_elseif();
	_else();
}

void parser::_call(){
	expect(TokenType::CALL);

	string func_name = _lexer.peek(1).lexeme;
	expect(TokenType::ID);

	vector<string> parameters;
	while(_lexer.peek(1).tokenType != TokenType::SEMI_COLON){
		parameters.push_back(_lexer.peek(1).lexeme);
		expect(TokenType::ID);
	}

	for (vector<string>::iterator i = parameters.begin(); i != parameters.end(); ++i) {
		//TAC += to_string(line_num) + " param " + *i + "\n";
		TAC += "param " + *i + "\n";
		line_num++;
	}
	
	//TAC += to_string(line_num) + " call " + func_name + ", " + to_string(parameters.size()) + ", " + newTemp() + "\n";
	TAC += "call " + func_name + ", " + to_string(parameters.size()) + ", " + newTemp() + "\n";
	TAC += "call " + func_name + ", " + to_string(parameters.size()) + ", " + newTemp() + "\n";
	expect(TokenType::SEMI_COLON);	
}

void parser::_function()
{
	expect(TokenType::FUNC);
	if (_lexer.peek(1).tokenType == TokenType::INT)
	{
		expect(TokenType::INT);
	}
	else if (_lexer.peek(1).tokenType == TokenType::CHAR)
	{
		expect(TokenType::CHAR);
	}
	expect(TokenType::ID);
	params();
	expect(TokenType::COLON);
	expect(TokenType::BEGIN);
	code();
	expect(TokenType::END);
}

void parser::params()
{
	if (_lexer.peek(1).tokenType == TokenType::ID)
	{
		param();
		params();
	}
	else
	{
		// DO NOTHING
	}
}

void parser::param()
{
	expect(TokenType::ID);
	if (_lexer.peek(1).tokenType == TokenType::INT)
	{
		expect(TokenType::INT);
	}
	else if (_lexer.peek(1).tokenType == TokenType::CHAR)
	{
		expect(TokenType::CHAR);
	}
}

int parser::multipleDeclaration()
{
	if (_lexer.peek(1).tokenType == TokenType::INT)
	{
		expect(TokenType::INT);
		return 1;
	}
	else if (_lexer.peek(1).tokenType == TokenType::CHAR)
	{
		expect(TokenType::CHAR);
		return 2;
	}
	else
	{
		expect(TokenType::COMMA);
		
		string id = _lexer.peek(1).lexeme;
		expect(TokenType::ID);

		if (_lexer.peek(1).tokenType == TokenType::ASSIGN)
		{
			line_num++;
			//TAC += to_string(line_num) + " " + id;
			TAC += id;
			expect(TokenType::ASSIGN);
			TAC += " = ";
			TAC += E();
			TAC += "\n";
		}
		int cond = multipleDeclaration();
		if (cond == 1)
		{
			addToSymbolTable("INT", id);
		}
		else if (cond == 2)
		{
			addToSymbolTable("CHAR", id);
		}
		return cond;
	}
}

void parser::code()
{
	if (_lexer.peek(1).tokenType == TokenType::ID)
	{
		string id = _lexer.peek(1).lexeme;
		expect(TokenType::ID);
		if (_lexer.peek(1).tokenType == TokenType::COMMA)
		{
			int cond = multipleDeclaration();
			if (cond == 1)
			{
				addToSymbolTable("INT", id);
			}
			else if (cond == 2)
			{
				addToSymbolTable("CHAR", id);
			}
			expect(TokenType::SEMI_COLON);
			code();
		}
		else if (_lexer.peek(1).tokenType == TokenType::INT)
		{
			expect(TokenType::INT);
			expect(TokenType::SEMI_COLON);
			addToSymbolTable("INT", id);
			code();
		}
		else if (_lexer.peek(1).tokenType == TokenType::CHAR)
		{
			expect(TokenType::CHAR);
			expect(TokenType::SEMI_COLON);
			addToSymbolTable("CHAR", id);
			code();
		}
		else
		{
			//TAC += to_string(line_num) + " " + id;
			TAC += id;
			expect(TokenType::ASSIGN);
			TAC += " = ";
			TAC += E();
			TAC += "\n";
			if (_lexer.peek(1).tokenType == TokenType::COMMA)
			{
				int cond = multipleDeclaration();
				if (cond == 1)
				{
					addToSymbolTable("INT", id);
				}
				else if (cond == 2)
				{
					addToSymbolTable("CHAR", id);
				}
			}
			else if (_lexer.peek(1).tokenType == TokenType::INT)
			{
				expect(TokenType::INT);
				addToSymbolTable("INT", id);
			}
			else if (_lexer.peek(1).tokenType == TokenType::CHAR)
			{
				expect(TokenType::CHAR);
				addToSymbolTable("CHAR", id);
			}
			expect(TokenType::SEMI_COLON);
			line_num++;
			code();
		}
	}
	else if (_lexer.peek(1).tokenType == TokenType::PRINT)
	{
		//TAC += to_string(line_num) + " ";
		TAC += print();
		TAC += "\n";
		line_num++;
		code();
	}
	else if (_lexer.peek(1).tokenType == TokenType::IF)
	{
		_if();
		code();
	}
	else if (_lexer.peek(1).tokenType == TokenType::FOR)
	{
		_for();
		line_num++;
		code();
	}
	else if (_lexer.peek(1).tokenType == TokenType::RETURN)
	{
		//TAC += to_string(line_num) + " ";
		TAC += _return();
		TAC += "\n";
		line_num++;
		code();
	}
	else if (_lexer.peek(1).tokenType == TokenType::IN)
	{
		//TAC += to_string(line_num) + " ";
		TAC += input();
		TAC += "\n";
		line_num++;
		code();
	}
	else if (_lexer.peek(1).tokenType == TokenType::CALL){
		_call();
		line_num++;
		code();
	}
	else
	{
		// Do NOTHING
	}
}

void parser::parserMain()
{
	z();
	fout_TAC.close();
}

void parser::z()
{
	if (_lexer.peek(1).tokenType == TokenType::FUNC)
	{
		_function();
		fout_TAC << TAC;
		TAC = "";
		z();
	}
	else
	{
		// DO NOTHING
	}
}

void parser::addToSymbolTable(string type, string symbol){
	
	fout_symbol_table << type << " " << symbol << " " << currentAddress << endl;
	if(type == "CHAR"){
		currentAddress += 1;
	}
	else if(type == "INT"){
		currentAddress += 4;
	}
}
