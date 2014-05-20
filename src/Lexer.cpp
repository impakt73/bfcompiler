#include <Lexer.h>
#include <iostream>

bool Lexer::Lex(const std::string& inInputText, std::vector<eToken>& outTokens)
{
    unsigned int textLength = inInputText.size();
    for(unsigned int index = 0; index < textLength; ++index)
    {
        switch(inInputText[index])
        {
            case '<':
            {
                outTokens.push_back(kToken_DecrementPointer);
                break;
            }

            case '>':
            {
                outTokens.push_back(kToken_IncrementPointer);
                break;
            }

            case '+':
            {
                outTokens.push_back(kToken_IncrementValue);
                break;
            }

            case '-':
            {
                outTokens.push_back(kToken_DecrementValue);
                break;
            }

            case '.':
            {
                outTokens.push_back(kToken_OutputValue);
                break;
            }

            case ',':
            {
                outTokens.push_back(kToken_InputValue);
                break;
            }

            case '[':
            {
                outTokens.push_back(kToken_BeginLoop);
                break;
            }

            case ']':
            {
                outTokens.push_back(kToken_EndLoop);
                break;
            }

            case ' ':
            case '\r':
            case '\n':
            {
                // Skip whitespace and newlines
                break;
            }

            default:
            {
                // Undefined symbol found
                std::cout << "Error! Undefined symbol: " << inInputText[index] << std::endl;
                return false;
            }
        }
    }

    return true;
}
