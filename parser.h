#ifndef _PARSER_H_
#define _PARSER_H_
#include "lexer.h"

//for future assignments leave it as it is
class parser
{
    lexer _lexer;
    ofstream fout_symbol_table;
    ofstream fout_TAC;
    int line_num;
    int temp_count;
    string TAC;
    int currentAddress;
    unordered_map<string, pair<string, string>> symbolTable;
	unordered_map<string, int> opCodeTable;
    
public:
    string newTemp();
    void syntax_error();
    token expect(TokenType expected_type);
    parser(const char filename[]);
    void readAndPrintAllInput();
    void resetPointer();
    void addToSymbolTable(string type, string symbol);
    string E();
    string T();
    string R();
    string F();
    string rPrime();
    void match(string strObj);
    string assign();
    void init();
    string X();   
    string print();
    string pst();
    void match_lexeme(string strObj);
    string condition();
    string ro();
    string _return();
    string input();
    void _for();
    void _if();
    void next();
    void _else();
    void _elseif();
    void _call();
    void _function();
    void params();
    void param();
    void code();
    int multipleDeclaration();
    void parserMain();
    void z();
    /*Terminal functions goes here use peek and expect*/
    /*use TokenType:: for token names for example
        expect(TokenType::ASSIGN);   //example function call
      */
	//all your parser function goes here
};
#endif
