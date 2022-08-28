#include "lexer.h"
using namespace std;
//for printing tokens names, Same as the enum defined in lexer.h
string reserved[] = {
    "END_OF_FILE",
    "FUNC",
    "INT",
    "CHAR",
    "CALL",
    "IF",
    "ELIF",
    "ELSE",
    "FOR",
    "PRINT",
    "PRINTLN",
    "RETURN",
    "IN",
    "ASSIGN",
    "ID",
    "NUMBER",
    "CHARACTER",
    "BEGIN",
    "END",
    "RELATION_OP",
    "ADD_OP",
    "SUBTRACT_OP",
    "MULTIPLY_OP",
    "DIVIDE_OP",
    "MOD_OP",
    "STRING",
    "COMMENT",
    "COMMA",
    "HASH",
    "COLON",
    "SEMI_COLON",
	};

token::token()
{
    this->lexeme = "";
    this->tokenType = TokenType::ERROR;
}

token::token(string lexeme, TokenType tokenType)
{
    this->lexeme = lexeme;
    this->tokenType = tokenType;
}

void token::Print()
{
    cout << "{" << lexeme << " , "
        << reserved[(int)tokenType] << "}\n";
}

int lexer::getCurrentPointer()
{
    return index;
}

void lexer::setCurrentPointer(int pos)
{
    if (pos >= 0 && pos < tokens.size())
        index = pos;
    else
        index = 0;
}

void lexer::Tokenize()//function that tokenizes your input stream
{
    vector<char>::iterator it = stream.begin();
    for (it = stream.begin(); it != stream.end(); it++){
        // Comma
        if (*it == ',') {
            tokens.push_back(token(string(""), TokenType::COMMA));
        }
        // Colon
        else if (*it == ':') {
            tokens.push_back(token(string(""), TokenType::COLON));
        }
        // Semi Colon
        else if (*it == ';') {
            tokens.push_back(token(string(""), TokenType::SEMI_COLON));
        }
        // Add Op || Number
        else if (*it == '+') {
            if (*(it + 1) >= 48 && *(it + 1) <= 58) {
                it++;
                string temp = "+";
                while (it != stream.end() && (*(it) >= 48 && *(it) <= 58)) {
                    temp.push_back(*it);
                    it++;
                }
                it--;
                tokens.push_back(token(string(temp), TokenType::NUMBER));
            }
            else{
                tokens.push_back(token(string(""), TokenType::ADD_OP));
            }
        }
        // Subtract Op || Number
        else if (*it == '-') {
            if (*(it + 1) >= 48 && *(it + 1) <= 58) {
                it++;
                string temp = "-";
                while (it != stream.end() && (*(it) >= 48 && *(it) <= 58)) {
                    temp.push_back(*it);
                    it++;
                }
                it--;
                tokens.push_back(token(string(temp), TokenType::NUMBER));
            }
            else {
                tokens.push_back(token(string(""), TokenType::SUBTRACT_OP));
            }
        }
        // Multiply Op
        else if (*it == '*') {
            tokens.push_back(token(string(""), TokenType::MULTIPLY_OP));
        }
        // Divide Op
        else if (*it == '/') {
            tokens.push_back(token(string(""), TokenType::DIVIDE_OP));
        }
        // Mod Op
        else if (*it == '%') {
            tokens.push_back(token(string(""), TokenType::MOD_OP));
        }
        // Equal to
        else if (*it == '=') {
            tokens.push_back(token(string(""), TokenType::EQUAL_TO_OP));
        }
        // Not Equal to
        else if (*it == '~') {
            if (*(it + 1) == '=') {
                tokens.push_back(token(string(""), TokenType::NOT_EQUAL_TO_OP));
                it++;
            }
        }
        // Greater than || Greater than Equal to 
        else if (*it == '>') {
            it++;
            if (*it == '=') {
                tokens.push_back(token(string(""), TokenType::GREATER_THAN_EQUAL_TO_OP));
            }
            else{
                tokens.push_back(token(string(""), TokenType::GREATER_THAN_OP));
                it--;
            }
        }
        // Less than || Less than Equal to || Assignment
        else if (*it == '<') {
            it++;
            if (*it == '=') {
                tokens.push_back(token(string(""), TokenType::LESS_THAN_EQUAL_TO_OP));
            }
            else if (*it == '-') {
                tokens.push_back(token(string(""), TokenType::ASSIGN));
            }
            else {
                tokens.push_back(token(string(""), TokenType::LESS_THAN_OP));
                it--;
            }
        }
        // String
        else if (*it == '"') {
            string temp = "";
            temp.push_back(*it);
            it++;
            while (it != stream.end() && *it != '"') {
                temp.push_back(*it);
                it++;
            }
            tokens.push_back(token(string(temp), TokenType::STRING));
        }
        // Comments
        else if (*it == '#') {
            it++;
            while (it != stream.end() && *it != '\n') {
                it++;
            };
            it--;
            tokens.push_back(token(string(""), TokenType::COMMENT));
        }
        // Character Literal
        else if (*it == '\'') {
            string temp = "";
            temp.push_back(*it);
            it++;
            while (it != stream.end() && *it != '\'' ) {
                temp.push_back(*it);
                it++;
            }
            it--;
            tokens.push_back(token(string(temp), TokenType::CHARACTER));
        }
        // Identifier || KEYWORDS
        else if ((*(it) >= 65 && *(it) <= 90) || (*(it) >= 97 && *(it) <= 122)) {
            string temp = "";
            temp.push_back(*it);
            it++;
            while (it != stream.end() && ((*(it) >= 65 && *(it) <= 90) || (*(it) >= 97 && *(it) <= 122) || (*(it) >= 48 && *(it) <= 58))) {
                temp.push_back(*it);
                it++;
            }
            it--;
            
            if (temp == "if") {
                tokens.push_back(token("", TokenType::IF));
            }
            else if (temp == "elif") {
                tokens.push_back(token("", TokenType::ELIF));
            }
            else if (temp == "else") {
                tokens.push_back(token("", TokenType::ELSE));
            }
            else if (temp == "func") {
                tokens.push_back(token("", TokenType::FUNC));
            }
            else if (temp == "begin") {
                tokens.push_back(token("", TokenType::BEGIN));
            }
            else if (temp == "end") {
                tokens.push_back(token("", TokenType::END));
            }
            else if (temp == "int") {
                tokens.push_back(token("", TokenType::INT));
            }
            else if (temp == "char") {
                tokens.push_back(token("", TokenType::CHAR));
            }
            else if (temp == "call") {
                tokens.push_back(token("", TokenType::CALL));
            }
            else if (temp == "return") {
                tokens.push_back(token("", TokenType::RETURN));
            }
            else if (temp == "print") {
                tokens.push_back(token("", TokenType::PRINT));
            }
            else if (temp == "println") {
                tokens.push_back(token("", TokenType::PRINTLN));
            }
            else if (temp == "in") {
                tokens.push_back(token("", TokenType::IN));
            }
            else if (temp == "for") {
                tokens.push_back(token("", TokenType::FOR));
            }
            else {
                tokens.push_back(token(string(temp), TokenType::ID));
            }
            


        }
        // Number
        else if ((*(it) >= 48 && *(it) <= 58)) {
            string temp = "";
            temp.push_back(*it);
            it++;
            while (it != stream.end() && (*(it) >= 48 && *(it) <= 58)) {
                temp.push_back(*it);
                it++;
            }
            it--;
            tokens.push_back(token(string(temp), TokenType::NUMBER));
        }
    }

	//push_back EOF token at end to identify End of File
    tokens.push_back(token(string(""), TokenType::END_OF_FILE));
}

lexer::lexer(const char filename[])
{
    //constructors: takes file name as an argument and store all
    //the contents of file into the class varible stream
    ifstream fin(filename);
    if (!fin) //if file not found
    {
        cout << "file not found" << endl;
    }
    else
    {
        char byte = 0;
        while (fin.get(byte))
        { //store file contents into stream
            if (byte != '\r')
                stream.push_back(byte);
        }
        stream.push_back(' ');//dummy spaces appended at the end
        stream.push_back(' ');
        //Tokenize function to get all the (token,lexeme) pairs
        Tokenize();
        //assigning tokens to iterator::pointer
        index = 0;
    }
}

lexer::lexer()
{
    index = -1;
}

void lexer::printRaw()
{
    //helper function to print the content of file
    vector<char>::iterator it = stream.begin();
    for (it = stream.begin(); it != stream.end(); it++)
    {
        cout << *it;
    }
    cout << endl;
}

token lexer::getNextToken()
{
    //this function will return single (token,lexeme) pair on each call
    //this is an iterator which is pointing to the beginning of vector of tokens
    token _token;
    if (index == tokens.size())
    {                       // return end of file if
        _token.lexeme = ""; // index is too large
        _token.tokenType = TokenType::END_OF_FILE;
    }
    else
    {
        _token = tokens[index];
        index = index + 1;
    }
    return _token;
}

void lexer::resetPointer()
{
    index = 0;
}

token lexer::peek(int howFar)
{
    if (howFar <= 0)
    { // peeking backward or in place is not allowed
        cout << "LexicalAnalyzer:peek:Error: non positive argument\n";
        exit(-1);
    }

    int peekIndex = index + howFar - 1;
    if (peekIndex > (tokens.size() - 1))
    {                                                 // if peeking too far
        return token("", TokenType::END_OF_FILE); // return END_OF_FILE
    }
    else
        return tokens[peekIndex];
}