#ifndef __LOGI_SYMBOL_REPOSITORY_H__
#define __LOGI_SYMBOL_REPOSITORY_H__

//Logi includes
#include "Types.h"

//std includes
#include <vector>
#include <string>
#include <map>
#include <fstream>

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

const U1 GLOBAL_VARIABLE_SIZE {37};
const U1 STACK_FRAME_SIZE {16};
const U1 LABEL_SIZE {20};
const U1 BASE_PROCEDURE_SIZE {37};

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
// GlobalVariables are 37 bytes in size:
//
// text:    QWORD (8)
// type:    BYTE (1)
// len:     QWORD (8)
// size:    QWORD (8)
// offset:  QWORD (8)
// line:    DWORD (4)
// -------------------
// TOTAL:    37
//
struct GlobalVariable : public Addressable
{
    U8 text;        //index to stringTable of where identifier begins
    GVType type;    //BYTE, WORD, DWORD or QWORD
    U8 len;         //number of elements if an array (defaults to 1)
    U8 size;        //total byte size
    S8 offset;      //offset below $TOP, address(g) = $TOP - offset
    U4 line;        //line in source code containing declaration
    //read from file
    static void read(GlobalVariable& g,std::ifstream& in)
    {
        in.read((char*)&g.text,8);
        U1 typeAsByte {0};
        in.read((char*)&typeAsByte,1);
        g.type = static_cast<GVType>(typeAsByte);
        in.read((char*)&g.len,8);
        in.read((char*)&g.size,8);
        in.read((char*)&g.offset,8);
        in.read((char*)&g.line,4);
    }
    //write to file
    void write(std::ofstream& out) const
    {
        out.write((const char*)&text,sizeof(Logi::U8));
        U1 typeAsByte = static_cast<U1>(type);
        out.write((const char*)&typeAsByte,sizeof(Logi::U1));
        out.write((const char*)&len,sizeof(Logi::U8));
        out.write((const char*)&size,sizeof(Logi::U8));
        out.write((const char*)&offset,sizeof(Logi::S8));
        out.write((const char*)&line,sizeof(Logi::U4));
    }
    //stream output
    friend std::ostream& operator<<(std::ostream& out,const GlobalVariable& gv);
};

//
// Stack frame is 16 bytes long.
//
struct StackFrame
{
    U8 text;            //index to stringTable of where identifier begins
    S4 fpOffset;        //+n or -n from $FP
    U4 line;            //line in source code containing declaration
    //read from file
    static void read(StackFrame& sf,std::ifstream& in)
    {
        in.read((char*)&sf.text,8);
        in.read((char*)&sf.fpOffset,4);
        in.read((char*)&sf.line,4);
    }
    //write to file
    void write(std::ofstream& out) const
    {
        out.write((const char*)&text,sizeof(Logi::U8));
        out.write((const char*)&fpOffset,sizeof(Logi::S4));
        out.write((const char*)&line,sizeof(Logi::U4));
    }
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

//
// Label is 20 bytes long.
//
struct Label : public Addressable
{
    //U8 address        //derived from Addressable
    U8 text;            //index to stringTable of where identifier begins
    U4 line;            //line in source code containing declaration
    //read from file
    static void read(Label& l,std::ifstream& in)
    {
        in.read((char*)&l.text,8);
        in.read((char*)&l.address,8);
        in.read((char*)&l.line,4);
    }
    //write to file
    void write(std::ofstream& out) const
    {
        out.write((const char*)&text,sizeof(Logi::U8));
        out.write((const char*)&address,sizeof(Logi::U8));
        out.write((const char*)&line,sizeof(Logi::U4));
    }
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
//
// PROCEDURE IS 37 BYTES LONG + TOTAL SIZE OF ARGS, LOCALS AND LABELS:
//
// address: QWORD (8)
// text:    QWORD (8)
// line:    DWORD (4)
// retVal:  BYTE (1)
// ret:     STACK FRAME (16)
// args:    16 * NUM ARGS
// locals:  16 * NUM LOCALS
// lables:  20 * NUM LABELS
//
struct Procedure : public Addressable
{
    //U8 address                        //derived from Addressable
    U8 text;                            //index to stringTable of where identifier begins
    U4 line;                            //line in source code containing declaration
    ProcedureReturn retVal;             //VOID or VALUE
    StackFrame ret;                     //return (if any)
    std::vector<StackFrame> args;       //arguments
    std::vector<StackFrame> locals;     //local variables
    std::vector<Label> labels;          //labels
    //read from file
    static void read(Procedure& p,std::ifstream& in)
    {
        in.read((char*)&p.text,8);
        in.read((char*)&p.address,8);
        in.read((char*)&p.line,4);
        U1 retValAsByte {0};
        in.read((char*)&retValAsByte,1);
        p.retVal = static_cast<ProcedureReturn>(retValAsByte);

        //read num args, locals and labels
        int numArgs = in.get();
        int numLocals = in.get();
        U2 numLabels;
        in.read((char*)&numLabels,2);

        //read return value (if any)
        if(p.retVal == ProcedureReturn::VALUE)
        {
            StackFrame::read(p.ret,in);
        }

        //read in arguments
        for(int i=0; i<numArgs; i++)
        {
            StackFrame arg;
            StackFrame::read(arg,in);
            p.args.push_back(arg);
        }

        //read in locals
        for(int i=0; i<numLocals; i++)
        {
            StackFrame local;
            StackFrame::read(local,in);
            p.locals.push_back(local);
        }

        //read in labels
        for(int i=0; i<numLabels; i++)
        {
            Label label;
            Label::read(label,in);
            p.labels.push_back(label);
        }
    }
    //write to file
    void write(std::ofstream& out) const
    {
        out.write((const char*)&text,sizeof(Logi::U8));
        out.write((const char*)&address,sizeof(Logi::U8));
        out.write((const char*)&line,sizeof(Logi::U4));
        
        retVal == VOID ? out.put(VOID) : out.put(VALUE);

        // write num arguments
        const U1 numArgs = static_cast<U1>(args.size());
        out.write((const char*)&numArgs,sizeof(Logi::U1));
        // write num locals
        const U1 numLocals = static_cast<U1>(locals.size());
        out.write((const char*)&numLocals,sizeof(Logi::U1));
        // write num labels
        const U2 numLabels = static_cast<U2>(labels.size());
        out.write((const char*)&numLabels,sizeof(Logi::U2));

        // write return value (if any)
        if(retVal == ProcedureReturn::VALUE) ret.write(out);

        // write arguments
        std::vector<StackFrame>::const_iterator args_it = args.begin();
        while(args_it != args.end())
        {
            args_it->write(out);
            ++args_it;
        }

        // write local variables
        std::vector<StackFrame>::const_iterator locals_it = locals.begin();
        while(locals_it != locals.end())
        {
            locals_it->write(out);
            ++locals_it;
        }

        // write labels
        std::vector<Label>::const_iterator labels_it = labels.begin();
        while(labels_it != labels.end())
        {
            labels_it->write(out);
            ++labels_it;
        }
    }
    //stream output
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
        Addressable* getAddressable(const int index);
        //get size of symbol table in bytes
        const U8 size() const;
        //write to file
        void write(std::ofstream& out) const;
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
        std::vector<std::string>& getStringTable();
        const int stringTableSize() const;
        friend std::ostream& operator<<(std::ostream& out,const SymbolRepository& sr);
    private:
        std::vector<std::string> stringTable;
        SymbolTable symbolTable;
        std::map<std::string,U8> symbolMap;
};

} //namespace Logi

#endif //__LOGI_SYMBOL_REPOSITORY_H__
