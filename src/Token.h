#pragma once

enum eToken
{
    kToken_Undefined = 0,
    kToken_IncrementPointer,
    kToken_DecrementPointer,
    kToken_IncrementValue,
    kToken_DecrementValue,
    kToken_OutputValue,
    kToken_InputValue,
    kToken_BeginLoop,
    kToken_EndLoop
};
