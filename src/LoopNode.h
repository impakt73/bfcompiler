#pragma once

#include <Node.h>

class LoopNode : public Node
{
public:
    LoopNode(void) : Node(kNodeType_Loop) {}
    ~LoopNode(void) {}

private:
    LoopNode(const LoopNode& other) = delete;
    LoopNode& operator=(const LoopNode& other) = delete;
};
