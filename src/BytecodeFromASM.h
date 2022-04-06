#ifndef __LOGI_BYTECODE_FROM_ASM_H__
#define __LOGI_BYTECODE_FROM_ASM_H__

//Logi includes
#include "Types.h"
#include "SymbolRepository.h"

//std includes
#include <vector>
#include <ostream>

namespace Logi
{

struct Token;
class Line;

//
// Provides a fluent interface for loading instructions
// line-by-line into bytecode. Stores the bytecode in an
// internal vector which can later be dumped to file.
//
class BytecodeFromASM
{
    public:
        BytecodeFromASM();
        void init(SymbolRepository* symbolRepository,const bool skip);
        void load(const Line& line);
        const U8 getCurrentByte() const;
        BytecodeFromASM& I();
        BytecodeFromASM& A();
        BytecodeFromASM& B();
        BytecodeFromASM& W();
        BytecodeFromASM& D();
        BytecodeFromASM& Q();
        BytecodeFromASM& F1();
        BytecodeFromASM& F2();
        BytecodeFromASM& C();
        BytecodeFromASM& R(unsigned int count=1);
        BytecodeFromASM& RF(unsigned int count=1);
        BytecodeFromASM& RD(unsigned int count=1);
        std::map<std::string,U8>& getAddressesToResolve();
        std::vector<U1>& getBytecode();
        //stream output
        friend std::ostream& operator<<(std::ostream& out,const BytecodeFromASM& li);
    private:
        U8 currentByte;
        SymbolRepository* symbolRepository;
        std::vector<Token>::const_iterator token_it;
        bool skip; //if true then skip loading the bytecode as in first pass we need to collect address information
        std::vector<U1> bytecode;
        std::map<std::string,U8> addressesToResolve;
};

} //namespace Logi

#endif //__LOGI_BYTECODE_FROM_ASM_H__
