//Logi includes
#include "../InstructionSet.h"
#include "../VirtualMachine.h"
#include "../Console.h"

namespace Logi
{

//
// INTERRUPT    FUNCTION ($R1)  DESCRIPTION
// -------------------------------------------------------------
// 5            0               returns the number of arguments
// 5            1               returns a command line argument
//
void InstructionSet::handleCommandLine()
{
    //set console color
    std::cout << Console::GREEN;

    // get the value in $R1
    const U1 R1 = (U1)vm->registers.R($R1);

    switch(R1)
    {
        case 0:
        {
            // return number of command line arguments
            // save in $R2
            vm->registers.R($R2) = vm->commandLine.size();
        }
        break;
        case 1:
        {
            // return a command line argument
            // $R2 = index to argument
            // $R3 = address of buffer where the argument can be stored
            // $R4 = 1 if a request is made for an argument that is not there
            // $R5 = length of the argument string (including null-termination character)
            const U8 R2 = vm->registers.R($R2);
            U8 R3 = vm->registers.R($R3);

            if(R2 < vm->commandLine.size())
            {
                vm->registers.R($R4) = 1;
                vm->registers.R($R5) = 0;
                return;
            }
            else
            {
                std::string arg = vm->commandLine.at(R2);

                // save to buffer
                for(int i=0; i<arg.length(); i++)
                {
                    (*vm->ram)(R3) = arg.at(i);
                    R3++;
                }
                (*vm->ram)(R3) = '\0'; // null-terminate string arg

                vm->registers.R($R4) = 0;
                vm->registers.R($R5) = arg.length() + 1;
            }
        }
        break;
        default:
        {
            std::string errorStr {"INTSTRUCTION_SET: interrupt 5 function ("};
            errorStr += std::to_string(R1);
            errorStr += ") not handled.";
            throw std::runtime_error(errorStr);
        }
    }

    //reset console color
    std::cout << Console::RESET;
}

} //namespace Logi
