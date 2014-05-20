#pragma once

#include <Node.h>
#include <string.h>

class Interpreter
{
public:
    Interpreter(void) { memset(mMemory, 0, sizeof(char)*sMemorySize); }
    ~Interpreter(void) {}

    bool Execute(Node* inRootNode);

private:
    Interpreter(const Interpreter& other) = delete;
    Interpreter& operator=(const Interpreter& other) = delete;

    bool ExecuteNode(Node* inNode);

    unsigned int mMemoryIndex = 0;
    static const int sMemorySize = 30000;
    char mMemory[sMemorySize];
};
