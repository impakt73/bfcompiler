#pragma once

#include <Node.h>
#include <CommandType.h>

class CommandNode : public Node
{
public:
    CommandNode(void) : Node(kNodeType_Command), mCommandType(kCommandType_Undefined), mCommandData(0) {}
    CommandNode(eCommandType inCommandType) : Node(kNodeType_Command), mCommandType(inCommandType), mCommandData(0) {}
    CommandNode(eCommandType inCommandType, int inCommandData) : Node(kNodeType_Command), mCommandType(inCommandType), mCommandData(inCommandData) {}
    ~CommandNode(void) {}

    inline eCommandType GetCommandType(void) const { return mCommandType; }
    inline int GetCommandData(void) const { return mCommandData; }

private:
    CommandNode(const CommandNode& other) = delete;
    CommandNode& operator=(const CommandNode& other) = delete;

    eCommandType mCommandType;

    int mCommandData;
};
