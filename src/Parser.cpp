#include <Parser.h>
#include <CommandNode.h>
#include <LoopNode.h>
#include <iostream>
#include <cassert>

bool Parser::Parse(const std::vector<eToken>& inTokens, Node **outParseTree)
{
    Node* rootNode = new Node(kNodeType_Root);
    Node* currentNode = rootNode;
    unsigned int tokenCount = inTokens.size();

    for(unsigned int index = 0; index < tokenCount; ++index)
    {
        switch(inTokens[index])
        {
            case kToken_IncrementPointer:
            {
                currentNode->InsertNode(new CommandNode(kCommandType_IncrementPointer));
                break;
            }

            case kToken_DecrementPointer:
            {
                currentNode->InsertNode(new CommandNode(kCommandType_DecrementPointer));
                break;
            }

            case kToken_IncrementValue:
            {
                currentNode->InsertNode(new CommandNode(kCommandType_IncrementValue));
                break;
            }

            case kToken_DecrementValue:
            {
                currentNode->InsertNode(new CommandNode(kCommandType_DecrementValue));
                break;
            }

            case kToken_OutputValue:
            {
                currentNode->InsertNode(new CommandNode(kCommandType_OutputValue));
                break;
            }

            case kToken_InputValue:
            {
                currentNode->InsertNode(new CommandNode(kCommandType_InputValue));
                break;
            }

            case kToken_BeginLoop:
            {
                LoopNode* loop = new LoopNode();
                currentNode->InsertNode(loop);
                currentNode = loop;
                break;
            }

            case kToken_EndLoop:
            {
                Node* parentNode = currentNode->GetParent();
                assert(parentNode != nullptr);
                currentNode = parentNode;
                break;
            }

            case kToken_Undefined:
            default:
            {
                std::cout << "Error! Undefined token encountered!" << std::endl;
                delete rootNode;
                return false;
            }
        }
    }

    *outParseTree = rootNode;
    return true;
}
