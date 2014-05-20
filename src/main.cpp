#include <iostream>
#include <Lexer.h>
#include <Parser.h>
#include <Interpreter.h>

int main()
{
    std::vector<eToken> tokens;

    if(!Lexer::Lex("++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++.", tokens))
    {
        std::cout << "Failed to lex input text!" << std::endl;
        return -1;
    }
    else
    {
        std::cout << "Successfully extracted " << tokens.size() << " tokens from input text!" << std::endl;
    }

    Node* rootNode = nullptr;

    if(!Parser::Parse(tokens, &rootNode))
    {
        std::cout << "Failed to parse tokens!" << std::endl;
        return -1;
    }
    else
    {
        std::cout << "Successfully parsed " << rootNode->GetChildren().size() << " nodes from tokens!" << std::endl;
    }

    std::cout << "Executing program..." << std::endl;

    Interpreter interpreter;
    if(!interpreter.Execute(rootNode))
    {
        std::cout << "Failed to execute program!" << std::endl;
        return -1;
    }

    std::cout << "Program executed successfully." << std::endl;

    return 0;
}

