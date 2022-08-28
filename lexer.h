#ifndef _LEXER_H_
#define _LEXER_H_
#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <cctype>
#include <unordered_map>
#include <iterator>
#include <bits/stdc++.h>
#include <utility>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

// all your tokens goes here
enum class TokenType
{
	END_OF_FILE = 0,
	FUNC = 1,
	INT = 2,
	CHAR = 3,
	CALL = 4,
	IF = 5,
	ELIF = 6,
	ELSE = 7,
	FOR = 8,
	PRINT = 9,
	PRINTLN = 10,
	RETURN = 11,
	IN = 12,
	ASSIGN = 13,
	ID = 14,
	NUMBER = 15,
	CHARACTER = 16,
	BEGIN = 17,
	END = 18,
	RELATION_OP = 19,
	STRING = 20,
	COMMENT = 21,
	COMMA = 22,
	HASH = 23,
	COLON = 24,
	SEMI_COLON = 25,
	ADD_OP = 26,
	SUBTRACT_OP = 27,
	MULTIPLY_OP = 28,
	DIVIDE_OP = 29,
	MOD_OP = 30,
	ERROR

};

// structure of a token
struct token
{
	string lexeme;
	TokenType tokenType; // enum type
	// constructor
	token(string lexeme, TokenType tokenType);
	// constructor default
	token();
	void Print();
};

class lexer
{
	vector<char> stream;  // used for storing file sample_code.cc content
	vector<token> tokens; // vector to store all (tokens,lexeme) pairs
	void Tokenize();      // populates tokens vector
	int index;

public:
	lexer();
	lexer(const char filename[]);
	void printRaw();		 // just print everything as it is present in file
	token getNextToken();		 // get next token
	void resetPointer();		 // reset pointer to start getting tokens from start
	int getCurrentPointer();	 // get where current pointer in tokens vector is
	void setCurrentPointer(int pos); // move current pointer to wherever
	token peek(int);		 // peek the next token
};

#endif // !_LEXER_H
