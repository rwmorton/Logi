#ifndef __LOGI_BYTECODE_FROM_ASM_H__
#define __LOGI_BYTECODE_FROM_ASM_H__

//Logi includes
#include "Types.h"

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
        void init();
        void begin(const Line& line);
        const U8 getCurrentByte() const;
        BytecodeFromASM& I();
        BytecodeFromASM& A();
        BytecodeFromASM& B();
        BytecodeFromASM& C();
        BytecodeFromASM& R(unsigned int count=1);
        BytecodeFromASM& F(unsigned int count=1);
        BytecodeFromASM& D(unsigned int count=1);
        //stream output
        friend std::ostream& operator<<(std::ostream& out,const BytecodeFromASM& li);
    private:
        U8 currentByte;
        std::vector<Token>::const_iterator token_it;
        std::vector<U1> bytecode;
};

} //namespace Logi

#endif //__LOGI_BYTECODE_FROM_ASM_H__
