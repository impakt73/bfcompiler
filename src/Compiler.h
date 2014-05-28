#pragma once

#include <Node.h>
#include <string>
#include <sstream>

class Compiler
{
public:
    Compiler(void) {}
    ~Compiler(void) {}

    std::string GenerateAssembly(Node* inRootNode);

private:
    Compiler(const Compiler& other) = delete;
    Compiler& operator=(const Compiler& other) = delete;

    void GenerateAssemblyForNode(Node* inNode, int inLoopId, std::stringstream& ioAssemblyOutputBuffer);

    static const std::string sPointerRegister;
    static const std::string sLineTerminator;
};
