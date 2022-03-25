#ifndef __LOGI_DEBUGGER_H__
#define __LOGI_DEBUGGER_H__

//Logi includes
#include "Types.h"
#include "Bytecode.h"

//std includes
#include <vector>

namespace Logi
{

//
// stores the table of contents which is the
// first 8 bytes of the executables symbol table
//
struct Contents
{
    U4 numGlobalVariables;   //number of global variable records in string table
    U4 numProcedures;        //number of procedure records in string table
};

//
// information in Contents is used to allocate an
// array of GlobalVarRec and ProcRec structures
//
struct GlobalVariable
{
    U8 text;        //index to stringTable of where identifier begins
    U1 type;        //SZ_BYTE, SZ_WORD, SZ_DWORD, SZ_QWORD
    U8 len;         //number of elements if an array
    U8 size;        //total byte size
    S8 offset;      //offset below $TOP, address(g) = $TOP - offset
    U4 line;        //line in source code containing declaration
};

struct StackFrame
{
    U8 text;            //index to stringTable of where identifier begins
    S4 fpOffset;        //+n or -n from $FP
    U4 line;            //line in source code containing declaration
};

struct Label
{
    U8 text;            //index to stringTable of where identifier begins
    U8 address;         //address of label
    U4 line;            //line in source code containing declaration
};

struct Procedure
{
    U8 text;                //index to stringTable of where identifier begins
    U8 address;             //address of procedure
    U4 line;                //line in source code containing declaration
    U1 nRet;                //0 = void return, 1 = returns a value
    U1 nArgs;               //number of arguments
    U1 nLocals;             //number of local variables
    U2 nLabels;             //number of labels
    StackFrame* ret {nullptr};
    StackFrame* args {nullptr};
    StackFrame* locals {nullptr};
    Label* labels;
};

struct DebugData
{
    struct Contents contents;
    struct GlobalVariable* globalVariables {nullptr};
    struct Procedure* procedures {nullptr};
    U1* stringTable;
};

struct HeaderRec {}; //TEMP

class Debugger
{
    friend class Bytecode;
    public:
        ~Debugger();
    private:
        DebugData data;
};

} //namespace Logi

#endif //__LOGI_DEBUGGER_H__
