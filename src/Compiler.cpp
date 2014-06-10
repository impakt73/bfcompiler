#include <Compiler.h>
#include <CommandNode.h>
#include <LoopNode.h>
#include <cassert>
#include <cstdlib>

const std::string Compiler::sPointerRegister = "edi";
const std::string Compiler::sLineTerminator = "\n";

std::string Compiler::GenerateAssembly(Node *inRootNode)
{
    assert(inRootNode->GetType() == kNodeType_Root);
    std::stringstream assemblyOutputBuffer;

    assemblyOutputBuffer << "global _start" << sLineTerminator;

    assemblyOutputBuffer << "section .data" << sLineTerminator;
    assemblyOutputBuffer << "   memory: times 30000 db 0x0" << sLineTerminator;
    assemblyOutputBuffer << sLineTerminator;

    assemblyOutputBuffer << "section .text" << sLineTerminator;
    assemblyOutputBuffer << sLineTerminator;

    assemblyOutputBuffer << "_start:" << sLineTerminator;

    assemblyOutputBuffer << "mov " << sPointerRegister << ", 0x0" << sLineTerminator;

    std::vector<Node*> childNodes = inRootNode->GetChildren();
    unsigned int childrenCount = childNodes.size();
    unsigned int loopCounter = 0;

    for(unsigned int index = 0; index < childrenCount; ++index)
    {
        GenerateAssemblyForNode(childNodes[index], &loopCounter, assemblyOutputBuffer);
    }

    assemblyOutputBuffer << "mov eax, 0x01" << sLineTerminator;
    assemblyOutputBuffer << "mov ebx, 0x0" << sLineTerminator;
    assemblyOutputBuffer << "int 0x80" << sLineTerminator;

    return assemblyOutputBuffer.str();
}

void Compiler::GenerateAssemblyForNode(Node *inNode, unsigned int *inLoopCounter, std::stringstream& ioAssemblyOutputBuffer)
{
    switch(inNode->GetType())
    {
        case kNodeType_Command:
        {
            CommandNode* commandNode = static_cast<CommandNode*>(inNode);
            int commandCount = commandNode->GetCommandData();
            switch(commandNode->GetCommandType())
            {
                case kCommandType_IncrementPointer:
                {
                    if(commandCount > 1)
                    {
                        ioAssemblyOutputBuffer << "add " << sPointerRegister << ", byte " << commandCount << sLineTerminator;
                    }
                    else
                    {
                        ioAssemblyOutputBuffer << "inc " << sPointerRegister << sLineTerminator;
                    }
                    break;
                }

                case kCommandType_DecrementPointer:
                {
                    if(commandCount > 1)
                    {
                        ioAssemblyOutputBuffer << "sub " << sPointerRegister << ", byte " << commandCount << sLineTerminator;
                    }
                    else
                    {
                        ioAssemblyOutputBuffer << "dec " << sPointerRegister << sLineTerminator;
                    }
                    break;
                }

                case kCommandType_IncrementValue:
                {
                    if(commandCount > 1)
                    {
                        ioAssemblyOutputBuffer << "add byte [memory + " << sPointerRegister << "], byte " << commandCount << sLineTerminator;
                    }
                    else
                    {
                        ioAssemblyOutputBuffer << "inc byte [memory + " << sPointerRegister << "]" << sLineTerminator;
                    }
                    break;
                }

                case kCommandType_DecrementValue:
                {
                    if(commandCount > 1)
                    {
                        ioAssemblyOutputBuffer << "sub byte [memory + " << sPointerRegister << "], byte " << commandCount << sLineTerminator;
                    }
                    else
                    {
                        ioAssemblyOutputBuffer << "dec byte [memory + " << sPointerRegister << "]" << sLineTerminator;
                    }
                    break;
                }

                case kCommandType_OutputValue:
                {
                    ioAssemblyOutputBuffer << "mov eax, 0x04" << sLineTerminator;
                    ioAssemblyOutputBuffer << "mov ebx, 0x01" << sLineTerminator;
                    ioAssemblyOutputBuffer << "mov ecx, memory" << sLineTerminator;
                    ioAssemblyOutputBuffer << "add ecx, " << sPointerRegister << sLineTerminator;
                    ioAssemblyOutputBuffer << "mov edx, 0x01" << sLineTerminator;
                    ioAssemblyOutputBuffer << "int 0x80" << sLineTerminator;
                    break;
                }

                case kCommandType_InputValue:
                {
                    ioAssemblyOutputBuffer << "mov eax, 0x03" << sLineTerminator;
                    ioAssemblyOutputBuffer << "mov ebx, 0x0" << sLineTerminator;
                    ioAssemblyOutputBuffer << "mov ecx, memory" << sLineTerminator;
                    ioAssemblyOutputBuffer << "add ecx, " << sPointerRegister << sLineTerminator;
                    ioAssemblyOutputBuffer << "mov edx, 0x01" << sLineTerminator;
                    ioAssemblyOutputBuffer << "int 0x80" << sLineTerminator;
                    break;
                }

                case kCommandType_Undefined:
                default:
                {
                    return;
                }
            }

            break;
        }

        case kNodeType_Loop:
        {
            std::string loopBeginLabel = "_Loop_Begin_" + std::to_string(*inLoopCounter);
            std::string loopEndLabel = "_Loop_End_" + std::to_string(*inLoopCounter);
            (*inLoopCounter)++;

            ioAssemblyOutputBuffer << loopBeginLabel << ":" << sLineTerminator;

            ioAssemblyOutputBuffer << "movsx eax, byte [memory + " << sPointerRegister << "]" << sLineTerminator;
            ioAssemblyOutputBuffer << "test eax, eax" << sLineTerminator;
            ioAssemblyOutputBuffer << "jz " << loopEndLabel << sLineTerminator;

            std::vector<Node*> childNodes = inNode->GetChildren();
            unsigned int childrenCount = childNodes.size();
            for(unsigned int index = 0; index < childrenCount; ++index)
            {
                GenerateAssemblyForNode(childNodes[index], inLoopCounter, ioAssemblyOutputBuffer);
            }

            ioAssemblyOutputBuffer << "jmp " << loopBeginLabel << sLineTerminator;

            ioAssemblyOutputBuffer << loopEndLabel << ":" << sLineTerminator;

            break;
        }

        case kNodeType_Root:
        case kNodeType_Undefined:
        default:
        {
            return;
        }
    }

    return;
}
