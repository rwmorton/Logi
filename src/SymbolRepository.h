#ifndef __LOGI_SYMBOL_REPOSITORY_H__
#define __LOGI_SYMBOL_REPOSITORY_H__

//Logi includes
#include "Types.h"

//std includes
#include <vector>
#include <string>

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

enum GVType
{
    BYTE = 0,
    WORD,
    DWORD,
    QWORD
};

//
// information in Contents is used to allocate an
// array of GlobalVarRec and ProcRec structures
//
struct GlobalVariable
{
    U8 text;        //index to stringTable of where identifier begins
    GVType type;    //BYTE, WORD, DWORD or QWORD
    U8 len;         //number of elements if an array
    U8 size;        //total byte size
    S8 offset;      //offset below $TOP, address(g) = $TOP - offset
    U4 line;        //line in source code containing declaration
    //stream output
    friend std::ostream& operator<<(std::ostream& out,const GlobalVariable& gv);
    static const std::vector<std::string> GVTypeStrings;
};

struct StackFrame
{
    U8 text;            //index to stringTable of where identifier begins
    S4 fpOffset;        //+n or -n from $FP
    U4 line;            //line in source code containing declaration
    //stream output
    friend std::ostream& operator<<(std::ostream& out,const StackFrame& sf);
};

struct Label
{
    U8 text;            //index to stringTable of where identifier begins
    U8 address;         //address of label
    U4 line;            //line in source code containing declaration
    //stream output
    friend std::ostream& operator<<(std::ostream& out,const Label& l);
};

enum ProcedureReturn
{
    VOID = 0,
    VALUE
};

struct Procedure
{
    U8 text;                            //index to stringTable of where identifier begins
    U8 address;                         //address of procedure
    U4 line;                            //line in source code containing declaration
    ProcedureReturn retVal;             //VOID or VALUE
    StackFrame ret;                     //return (if any)
    std::vector<StackFrame> args;       //arguments
    std::vector<StackFrame> locals;     //local variables
    std::vector<Label> labels;          //labels
    friend std::ostream& operator<<(std::ostream& out,const Procedure& p);
};

//
// Maintains a list of global variables and procedures.
//
class SymbolTable
{
    public:
        //add global variable
        void addGlobalVariable(const GlobalVariable& gv);
        //add procedure
        void addProcedure(const Procedure& proc);
        //stream output
        friend std::ostream& operator<<(std::ostream& out,const SymbolTable& st);
    private:
        std::vector<GlobalVariable> globalVariables;
        std::vector<Procedure> procedures;
};

//
// stringVector is used to store identifier names
// symbolTable stores all the global variables
// and procedures used by the program.
//
class SymbolRepository
{
    public:
        //add identifier to the string vector
        void addIdentifier(const std::string& id);
        friend std::ostream& operator<<(std::ostream& out,const SymbolRepository& sr);
    private:
        std::vector<std::string> stringVector;
        SymbolTable symbolTable;
};

} //namespace Logi

#endif //__LOGI_SYMBOL_REPOSITORY_H__
