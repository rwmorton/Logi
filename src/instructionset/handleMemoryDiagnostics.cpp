//Logi includes
#include "../InstructionSet.h"
#include "../VirtualMachine.h"
#include "../Console.h"

namespace Logi
{

//
// INTERRUPT    FUNCTION ($R1)  DESCRIPTION
// -------------------------------------------------------------
// 6            0               returns the status of the virtual machine memory
// 6            1               returns status of host OS memory
//
void InstructionSet::handleMemoryDiagnostics()
{
    //set console color
    std::cout << Console::GREEN;

    // get the value in $R1
    const U1 R1 = (U1)vm->registers.R($R1);

    switch(R1)
    {
        case 0:
        {
            // returns status of VM memory
            // $R2 = size in bytes of the bytecode segment
            // $R3 = size in bytes of the heap segment
            // $R4 = size in bytes of the stack segment
            // $R5 = total memory allocated, in bytes
            vm->registers.R($R2) = vm->registers.R($BE) + 1;
            vm->registers.R($R3) = (vm->registers.R($HE) - vm->registers.R($HS)) + 1;
            vm->registers.R($R4) = (vm->registers.R($TOP) - vm->registers.R($SS)) + 1;
            vm->registers.R($R5) = vm->registers.R($TOP) + 1;
        }
        break;
        case 1:
        {
            // TODO
            throw std::runtime_error("INSTRUCTION_SET: interrupt 6 function 1 not implemented yet.");
        }
        break;
        default:
        {
            std::string errorStr {"INTSTRUCTION_SET: interrupt 6 function ("};
            errorStr += std::to_string(R1);
            errorStr += ") not handled.";
            throw std::runtime_error(errorStr);
        }
    }

    //reset console color
    std::cout << Console::RESET;
}

} //namespace Logi
