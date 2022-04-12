#ifndef __LOGI_DEBUG_PRINTER_H__
#define __LOGI_DEBUG_PRINTER_H__

//Logi includes
#include "Types.h"

//std includes
#include <ostream>

namespace Logi
{

class VirtualMachine;

class DebugPrinter
{
    friend class VirtualMachine;
    public:
        DebugPrinter(VirtualMachine& vm);
        void begin(const U8 currentByte);
        DebugPrinter& I();
        void I_end();
        DebugPrinter& R(int count=1);
        void R_end();
        DebugPrinter& RF(int count=1);
        void RF_end();
        DebugPrinter& RD(int count=1);
        void RD_end();
        void B();
        void W();
        void D();
        void Q();
        void F1();
        void F2();
        void A();
    private:
        U8 currentByte;
        VirtualMachine& vm;
        std::ostream& out;
};

} //namespace Logi

#endif //__LOGI_DEBUG_PRINTER_H__
