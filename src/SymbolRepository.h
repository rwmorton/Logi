#ifndef __LOGI_SYMBOL_REPOSITORY_H__
#define __LOGI_SYMBOL_REPOSITORY_H__

//Logi includes
#include "Types.h"

//std includes
#include <vector>
#include <string>
#include <map>

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
    BYTE    = 1,
    WORD    = 2,
    DWORD   = 4,
    QWORD   = 8
};

//
// Allows us to resolve addresses to global variables, procedures and labels
// once the initial assembly has been loaded and bytecode is being generated.
//
struct Addressable
{
    virtual ~Addressable() {}
    U8 address;
    U8 atByte;      //which byte does this addressable begin at?
};

//
// information in Contents is used to allocate an
// array of GlobalVarRec and ProcRec structures
//
struct GlobalVariable : public Addressable
{
    U8 text;        //index to stringTable of where identifier begins
    GVType type;    //BYTE, WORD, DWORD or QWORD
    U8 len;         //number of elements if an array (defaults to 1)
    U8 size;        //total byte size
    S8 offset;      //offset below $TOP, address(g) = $TOP - offset
    U4 line;        //line in source code containing declaration
    //stream output
    friend std::ostream& operator<<(std::ostream& out,const GlobalVariable& gv);
};

struct StackFrame
{
    U8 text;            //index to stringTable of where identifier begins
    S4 fpOffset;        //+n or -n from $FP
    U4 line;            //line in source code containing declaration
    //stream output
    friend std::ostream& operator<<(std::ostream& out,const StackFrame& sf);
};

/*
.PL mylabel
LQI $R1,-62
MOV $R2,$R1
LAI $R3, mylabel

Given the above series of statements, the address of mylabel
will be the address of the first byte of the instruction
following the label directive. In the above case the label
mylabel will represent the address of the LQI opcode in the
instruction directly beneath it.

When this labels identifier is encountered elsewhere in the
source file the assembler will replace the identifier with
the address associated with the label (e.g. address of LQI).
*/
struct Label : public Addressable
{
    U8 text;            //index to stringTable of where identifier begins
    //U8 address;         //address of label
    U4 line;            //line in source code containing declaration
    //stream output
    friend std::ostream& operator<<(std::ostream& out,const Label& l);
};

enum ProcedureReturn
{
    VOID = 0,
    VALUE
};

/*
.PB myfunction
LQI $R1,24
INT 0
.PL myfunction_L1
LQI $R1,20
INT 0
.PE

The procedures identifier represents the address
of the first byte of the first instruction in the
procedure. In the example above when the identifier
myfunction is used as an operand in an instruction
it will be replaced by the address of the first byte
of the LQI $R1,24 instruction.

The label myfunction_L1 represents the address of
the first byte of the LQI $R1,20 instruction. When
this label is encountered as an operand in an
instruction the assembler will replace it with the
corresponding address.
*/
struct Procedure : public Addressable
{
    U8 text;                            //index to stringTable of where identifier begins
    //U8 address;                         //address of procedure
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
        //add label that is not a procedure
        void addLabel(const Label& label);
        //get addressable at index
        Addressable* getAddressable(const int index)
        {
            return addressablesMap.find(index)->second;
        }
        //stream output
        friend std::ostream& operator<<(std::ostream& out,const SymbolTable& st);
    private:
        std::vector<GlobalVariable> globalVariables;
        std::vector<Procedure> procedures;
        std::vector<Label> labels; //that are not procedures
        std::map<int,Addressable*> addressablesMap; //key is index in string table
};

//
// stringTable is used to store identifier names
// symbolTable stores all the global variables
// and procedures used by the program.
//
class SymbolRepository
{
    public:
        //add identifier to the string vector
        const U8 addIdentifier(const std::string& id);
        const std::string& getIdentifier(const int index) const;
        const int getIdentifier(const std::string& id) const;
        //add label address to the symbol map
        void addLabelAddr(const std::string& id,const U8 addr);
        const U8 getAddress(const std::string& id) const;
        SymbolTable& getSymbolTable();
        const int indexInStringTable(const std::string& id) const;
        friend std::ostream& operator<<(std::ostream& out,const SymbolRepository& sr);
    private:
        std::vector<std::string> stringTable;
        SymbolTable symbolTable;
        std::map<std::string,U8> symbolMap;
};

} //namespace Logi

#endif //__LOGI_SYMBOL_REPOSITORY_H__
