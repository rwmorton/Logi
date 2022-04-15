//Logi includes
#include "../InstructionSet.h"
#include "../VirtualMachine.h"
#include "../Console.h"

namespace Logi
{

//
// INTERRUPT    FUNCTION ($R1)  DESCRIPTION
// -------------------------------------------------------------
// 4            0               returns the current UTC time
// 4            1               decomposes UTC time into date and time components
// 4            2               converts UTC to local time
// 4            3               converts a date into seconds since the epoch
// 4            4               creates a string representation of time
// 4            5               computes the difference between two times
// 4            6               performance timer
//
void InstructionSet::handleTimeDate()
{
    //set console color
    std::cout << Console::GREEN;

    // get the value in $R1
    const U1 R1 = (U1)vm->registers.R($R1);

    switch(R1)
    {
        case 0:
        {
            // returns current UTC time
            throw std::runtime_error("INSTRUCTION_SET: interrupt 4 function 0 not implemented yet.");
        }
        break;
        case 1:
        {
            // decompose UTC time
            throw std::runtime_error("INSTRUCTION_SET: interrupt 4 function 1 not implemented yet.");
        }
        break;
        case 2:
        {
            // convert UTC time to local time
            throw std::runtime_error("INSTRUCTION_SET: interrupt 4 function 2 not implemented yet.");
        }
        break;
        case 3:
        {
            // convert date into seconds since the epoch
            throw std::runtime_error("INSTRUCTION_SET: interrupt 4 function 3 not implemented yet.");
        }
        break;
        case 4:
        {
            // create a string representation of time
            throw std::runtime_error("INSTRUCTION_SET: interrupt 4 function 4 not implemented yet.");
        }
        break;
        case 5:
        {
            // compute the difference between two times
            throw std::runtime_error("INSTRUCTION_SET: interrupt 4 function 5 not implemented yet.");
        }
        break;
        case 6:
        {
            // performance timer
            throw std::runtime_error("INSTRUCTION_SET: interrupt 4 function 6 not implemented yet.");
        }
        break;
        default:
        {
            std::string errorStr {"INTSTRUCTION_SET: interrupt 4 function ("};
            errorStr += std::to_string(R1);
            errorStr += ") not handled.";
            throw std::runtime_error(errorStr);
        }
    }

    //reset console color
    std::cout << Console::RESET;
}

} //namespace Logi
