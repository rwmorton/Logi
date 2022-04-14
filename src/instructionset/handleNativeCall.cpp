//Logi includes
#include "../InstructionSet.h"
#include "../VirtualMachine.h"
#include "../Console.h"

namespace Logi
{

//
// INTERRUPT    FUNCTION ($R1)  DESCRIPTION
// -------------------------------------------------------------
// 9            0               Acquires a handle to a shared library
// 9            1               Invokes a native method from a shared library
// 9            2               Frees the shared library
//
// all shared libraries must export the following::
//
// void gateway(const std::string &in, const std::string &out);
//
// for the instruction to invoke. in and out are JSON files.
//
void InstructionSet::handleNativeCall()
{
    //set console color
    std::cout << Console::GREEN;

    // get the value in $R1
    const U1 R1 = (U1)vm->registers.R($R1);

    switch(R1)
    {
        case 0:
        {
            //load shared library
        }
        break;
        case 1:
        {
            //invoke gateway method
        }
        break;
        case 2:
        {
            //free shared library
        }
        break;
        default:
        {
            std::string errorStr {"INTSTRUCTION_SET: interrupt 9 function ("};
            errorStr += std::to_string(R1);
            errorStr += ") not handled.";
            throw std::runtime_error(errorStr);
        }
    }

    //reset console color
    std::cout << Console::RESET;
}

} //namespace Logi
