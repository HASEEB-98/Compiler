#ifndef _PARSER_H_
#define _PARSER_H_
#include "lexer.h"
//for future assignments leave it as it is
class parser
{
    lexer _lexer;
public:
    void syntax_error();
    token expect(TokenType expected_type);
    parser(const char filename[]);
    void readAndPrintAllInput();
    void resetPointer();
    void E();
    void T();
    void R();
    void F();
    void rPrime();
    void match(string strObj);
    void assign();
    void init();
    void X();
    void print();
    void pst();
    void match_lexeme(string strObj);
    void condition();
    void ro();
    void _return();
    void input();
    void _for();
    void _if();
    void next();
    void _else();
    void _elseif();
    void _function();
    void params();
    void param();
    void code();
    void Q();
    void parserMain();
    void z();
    /*Terminal functions goes here use peek and expect*/
    /*use TokenType:: for token names for example
        expect(TokenType::ASSIGN);   //example function call
      */
	//all your parser function goes here
};
#endif
