#include "parser.h"

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
}

void parser::readAndPrintAllInput() //read and print allinputs (provided)
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

void parser::E(){
    T();
	R();
}

void parser::R(){
    if (_lexer.peek(1).tokenType == TokenType::ADD_OP)
	{
		expect(TokenType::ADD_OP);
		T();
		R();
	}
	else if (_lexer.peek(1).tokenType == TokenType::SUBTRACT_OP)
	{
		expect(TokenType::SUBTRACT_OP);
		T();
		R();
	}
	else
	{
	}
}

void parser::T(){
    F();
	rPrime();
}

void parser::F(){
    if (_lexer.peek(1).tokenType == TokenType::ID)
	{
        expect(TokenType::ID);
	}
	else if (_lexer.peek(1).tokenType == TokenType::NUMBER)
	{
        expect(TokenType::NUMBER);
	}
	else
	{
		cout << "Error-Bad Token" << endl;
	}
}

void parser::rPrime(){
    if (_lexer.peek(1).tokenType == TokenType::MULTIPLY_OP)
	{
        expect(TokenType::MULTIPLY_OP);
		F();
	}
	else if (_lexer.peek(1).tokenType == TokenType::DIVIDE_OP)
	{
        expect(TokenType::DIVIDE_OP);
		F();
	}
	else if (_lexer.peek(1).tokenType == TokenType::MOD_OP)
	{
        expect(TokenType::DIVIDE_OP);
		F();
	}
	else
	{
	}
}

// Assignment Start
void parser::assign()
{
    expect(TokenType::ID);
    expect(TokenType::ASSIGN);
	E();
    expect(TokenType::SEMI_COLON);
}

void parser::init(){
    expect(TokenType::ID);
	X();
}

void parser::X(){
    if (_lexer.peek(1).tokenType == TokenType::ASSIGN)
	{
        expect(TokenType::ASSIGN);
		E();
        expect(TokenType::SEMI_COLON);
	}
    else if (_lexer.peek(1).tokenType == TokenType::INT)
    {
        expect(TokenType::INT);
        expect(TokenType::SEMI_COLON);
        match("SEMICOLON");
    }
    else if (_lexer.peek(1).tokenType == TokenType::CHAR)
    {
        expect(TokenType::CHAR);
        expect(TokenType::SEMI_COLON);
    }
	else
	{
		
	}
}

void parser::print(){
    if (_lexer.peek(1).tokenType == TokenType::PRINT)
	{
		expect(TokenType::CHAR);
		pst();
		expect(TokenType::SEMI_COLON);
	}
}

void parser::pst(){
    if (_lexer.peek(1).tokenType == TokenType::STRING)
	{
		expect(TokenType::STRING);
	}
	else
	{
		E();
	}
}

void parser::condition(){

	E();
	ro();
	E();
}

void parser::ro(){
    if (_lexer.peek(1).tokenType == TokenType::EQUAL_TO_OP)
	{
		expect(TokenType::EQUAL_TO_OP);
	}
	else if (_lexer.peek(1).tokenType == TokenType::LESS_THAN_OP)
	{
		expect(TokenType::LESS_THAN_OP);
	}
	else if (_lexer.peek(1).tokenType == TokenType::LESS_THAN_EQUAL_TO_OP)
	{
		expect(TokenType::LESS_THAN_EQUAL_TO_OP);
	}
	else if (_lexer.peek(1).tokenType == TokenType::GREATER_THAN_OP)
	{
		expect(TokenType::GREATER_THAN_OP);
	}
	else if (_lexer.peek(1).tokenType == TokenType::GREATER_THAN_EQUAL_TO_OP)
	{
		expect(TokenType::GREATER_THAN_EQUAL_TO_OP);
	}
	else if (_lexer.peek(1).tokenType == TokenType::NOT_EQUAL_TO_OP)
	{
		expect(TokenType::NOT_EQUAL_TO_OP);
	}
	else
	{
		cout << "Bad Token..." << endl;
	}
}

void parser::_return(){
	expect(TokenType::RETURN);
	E();
	expect(TokenType::SEMI_COLON);
}

void parser::input(){
    expect(TokenType::IN);
    expect(TokenType::ID);
    expect(TokenType::SEMI_COLON);
}

void parser::_for(){

    expect(TokenType::FOR);

    expect(TokenType::ID);
    expect(TokenType::ASSIGN);
	E();
    expect(TokenType::COMMA);

	condition();
    expect(TokenType::COMMA);

	expect(TokenType::ID);
    expect(TokenType::ASSIGN);
	E();
    expect(TokenType::COLON);

    expect(TokenType::BEGIN);
	code();
    expect(TokenType::END);
}

void parser::_if(){
    expect(TokenType::IF);
	condition();
    expect(TokenType::COLON);
    expect(TokenType::BEGIN);
	code();
    expect(TokenType::END);
	next();
}

void parser::next(){
    _else();
}

void parser::_else(){
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

void parser::_elseif(){

}

void parser::_function(){

    expect(TokenType::FUNC);
	if (_lexer.peek(1).tokenType == TokenType::CHAR || _lexer.peek(1).tokenType == TokenType::INT)
	{
        expect(TokenType::FUNC);
	}
	expect(TokenType::ID);
	// params();
    expect(TokenType::COLON);
    expect(TokenType::BEGIN);
	code();
    expect(TokenType::END);
}

void parser::params(){
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
void parser::param(){
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
void parser::code(){
    if (_lexer.peek(1).tokenType == TokenType::ID)
	{

		match("IDENTIFIER");
        if (_lexer.peek(1).tokenType == TokenType::INT)
        {
            expect(TokenType::INT);
            expect(TokenType::SEMI_COLON);
			code();
        }
        else if (_lexer.peek(1).tokenType == TokenType::CHAR)
        {
            expect(TokenType::CHAR);
            expect(TokenType::SEMI_COLON);
			code();
        }
		else
		{
            expect(TokenType::ASSIGN);
			E();
			if (_lexer.peek(1).tokenType == TokenType::INT)
            {
                expect(TokenType::INT);
            }
            else if (_lexer.peek(1).tokenType == TokenType::CHAR)
            {
                expect(TokenType::CHAR);
            }
			match("SEMICOLON");
			code();
		}
	}
	else if (_lexer.peek(1).tokenType == TokenType::PRINT)
	{
		print();
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
		code();
	}
	else if (_lexer.peek(1).tokenType == TokenType::RETURN)
	{
		_return();
		code();
	}
	else if (_lexer.peek(1).tokenType == TokenType::IN)
	{
		input();
		code();
	}
	else
	{
		// Do NOTHING
	}
}
void parser::Q(){

}
void parser::parserMain(){
    _function();
	z();
}

void parser::z(){
    if (_lexer.peek(1).tokenType == TokenType::FUNC)
	{
        expect(TokenType::FUNC);   
		z();
	}
	else
	{

		// DO NOTHING
	}
}


