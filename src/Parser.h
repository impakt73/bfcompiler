#pragma once

#include <Token.h>
#include <vector>
#include <Node.h>

class Parser
{
public:
    static bool Parse(const std::vector<eToken>& inTokens, Node** outParseTree);

private:
    Parser(void) {}
    ~Parser(void) {}

    Parser(const Parser& other) = delete;
    Parser& operator=(const Parser& other) = delete;

    inline static int GetOperationCount(unsigned int& ioCurrentIndex, const std::vector<eToken>& inTokens, eToken inInstructionToken);
};
