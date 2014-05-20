#pragma once

#include <Token.h>
#include <vector>
#include <string>

class Lexer
{
public:
    static bool Lex(const std::string& inInputText, std::vector<eToken>& outTokens);

private:
    Lexer(void) {}
    ~Lexer(void) {}

    Lexer(const Lexer& other) = delete;
    Lexer& operator=(const Lexer& other) = delete;
};
