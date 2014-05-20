#pragma once

enum eCommandType
{
    kCommandType_Undefined = 0,
    kCommandType_IncrementPointer,
    kCommandType_DecrementPointer,
    kCommandType_IncrementValue,
    kCommandType_DecrementValue,
    kCommandType_OutputValue,
    kCommandType_InputValue
};
