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
                int operationCount = GetOperationCount(index, inTokens, kToken_IncrementPointer);
                currentNode->InsertNode(new CommandNode(kCommandType_IncrementPointer, operationCount));
                break;
            }

            case kToken_DecrementPointer:
            {
                int operationCount = GetOperationCount(index, inTokens, kToken_DecrementPointer);
                currentNode->InsertNode(new CommandNode(kCommandType_DecrementPointer, operationCount));
                break;
            }

            case kToken_IncrementValue:
            {
                int operationCount = GetOperationCount(index, inTokens, kToken_IncrementValue);
                currentNode->InsertNode(new CommandNode(kCommandType_IncrementValue, operationCount));
                break;
            }

            case kToken_DecrementValue:
            {
                int operationCount = GetOperationCount(index, inTokens, kToken_DecrementValue);
                currentNode->InsertNode(new CommandNode(kCommandType_DecrementValue, operationCount));
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

int Parser::GetOperationCount(unsigned int &ioCurrentIndex, const std::vector<eToken>& inTokens, eToken inInstructionToken)
{
    int operationCount = 1;
    int currentIndex = ioCurrentIndex + 1;
    unsigned int tokenCount =inTokens.size();
    for(; currentIndex < tokenCount; currentIndex++)
    {
        if(inTokens[currentIndex] == inInstructionToken)
            operationCount++;
        else
            break;
    }
    ioCurrentIndex = currentIndex - 1;
    return operationCount;
}
