#include <Interpreter.h>
#include <CommandNode.h>
#include <LoopNode.h>

#include <iostream>
#include <cassert>

bool Interpreter::Execute(Node* inRootNode)
{
    assert(inRootNode->GetType() == kNodeType_Root);

    std::vector<Node*> childNodes = inRootNode->GetChildren();
    unsigned int childrenCount = childNodes.size();

    for(unsigned int index = 0; index < childrenCount; ++index)
    {
        if(!ExecuteNode(childNodes[index]))
            return false;
    }

    return true;
}

bool Interpreter::ExecuteNode(Node* inNode)
{
    switch(inNode->GetType())
    {
        case kNodeType_Command:
        {
            CommandNode* commandNode = static_cast<CommandNode*>(inNode);
            switch(commandNode->GetCommandType())
            {
                case kCommandType_IncrementPointer:
                {
                    mMemoryIndex++;
                    break;
                }

                case kCommandType_DecrementPointer:
                {
                    mMemoryIndex--;
                    break;
                }

                case kCommandType_IncrementValue:
                {
                    mMemory[mMemoryIndex]++;
                    break;
                }

                case kCommandType_DecrementValue:
                {
                    mMemory[mMemoryIndex]--;
                    break;
                }

                case kCommandType_OutputValue:
                {
                    std::cout << mMemory[mMemoryIndex];
                    break;
                }

                case kCommandType_InputValue:
                {
                    std::cin >> mMemory[mMemoryIndex];
                    break;
                }

                case kCommandType_Undefined:
                default:
                {
                    return false;
                }
            }

            break;
        }

        case kNodeType_Loop:
        {
            std::vector<Node*> childNodes = inNode->GetChildren();
            unsigned int childrenCount = childNodes.size();
            while(mMemory[mMemoryIndex] != 0)
            {
                for(unsigned int index = 0; index < childrenCount; ++index)
                {
                    if(!ExecuteNode(childNodes[index]))
                        return false;
                }
            }

            break;
        }

        case kNodeType_Root:
        case kNodeType_Undefined:
        default:
        {
            return false;
        }
    }

    return true;
}
