#pragma once

#include <Node.h>
#include <CommandType.h>

class CommandNode : public Node
{
public:
    CommandNode(void) : Node(kNodeType_Command), mCommandType(kCommandType_Undefined) {}
    CommandNode(eCommandType inCommandType) : Node(kNodeType_Command), mCommandType(inCommandType) {}
    ~CommandNode(void) {}

    inline eCommandType GetCommandType(void) const { return mCommandType; }

private:
    CommandNode(const CommandNode& other) = delete;
    CommandNode& operator=(const CommandNode& other) = delete;

    eCommandType mCommandType;
};
