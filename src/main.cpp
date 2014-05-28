#include <iostream>
#include <Lexer.h>
#include <Parser.h>
#include <Interpreter.h>
#include <Compiler.h>
#include <fstream>
#include <sstream>

int main(int argc, char** argv)
{
    if(argc != 2)
    {
        std::cout << "Invalid arguments!" << std::endl;
        std::cout << "Usage: bfcompiler FILE" << std::endl;
        return -1;
    }

    std::ifstream sourceInput(argv[1], std::ios::in);
    if(!sourceInput.is_open())
    {
        std::cout << "Failed to open input file '" << argv[1] << "'!" << std::endl;
        return -1;
    }
    std::stringstream sourceBuffer;
    while(sourceInput.good())
    {
        std::string sourceLine;
        std::getline(sourceInput, sourceLine);
        sourceBuffer << sourceLine;
    }
    sourceInput.close();

    std::vector<eToken> tokens;

    //if(!Lexer::Lex("++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++.", tokens))
    //if(!Lexer::Lex("+++[>+++++++++++++++++++++++++++++++++.<-]", tokens))
    if(!Lexer::Lex(sourceBuffer.str(), tokens))
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
        delete rootNode;
        return -1;
    }

    Compiler compiler;
    std::cout << "Generating Assembly..." << std::endl;
    std::string asmOutput = compiler.GenerateAssembly(rootNode);
    const std::string outputName = "bfgen.asm";
    std::ofstream outputStream(outputName, std::ios::out);
    if(outputStream.is_open())
    {
        outputStream << asmOutput;
        outputStream.close();

        std::cout << "Assembly Written to : " << outputName << std::endl;
    }
    else
    {
        std::cout << "Failed to Write Assembly to : " << outputName << std::endl;
    }

    delete rootNode;
    std::cout << "Program executed successfully." << std::endl;

    return 0;
}

