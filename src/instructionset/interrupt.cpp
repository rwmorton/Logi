//Logi includes
#include "../InstructionSet.h"
#include "../VirtualMachine.h"
#include "../Console.h"

//std includes
#include <fstream>
#include <iostream>

namespace Logi
{

//
// Accepts an integer argument (the interrupt vector) which
// is an index into one of the virtual machines iterrupt service
// routines. A switch statement is used to redirect the virtual
// machines execution path to the appropriate service routine.
//
// each interrupt vector value (INT 0, INT 4 etc.) corresponds to
// a specific interrupt handler (handleFileIO etc.). Each handler,
// in turn, will call a different function depending on the value
// of the $R1 register. Thus each interrupt handler is associated
// with several possible routines.
//
// INTERRUPT    FAMILY OF FUNCTIONS
// -----------------------------------------------
// 0            File I/O
// 1            File management
// 2            Process management
// 3            Breakpoints
// 4            Time and date calls
// 5            Handling command-line arguments
// 6            Memory diagnostics
// 7            Dynamic memory allocation
// 8            Math functions
// 9            Interfacing with native code
// 10           Interprocess communication
//
void InstructionSet::handleInterrupt(U1 byte)
{
    if(!interruptOn) return; //interrupts are disabled

    switch(byte)
    {
        case 0:
        {
            handleFileIO();
        }
        break;
        case 1:
        {
            //handle vector 1
            throw std::runtime_error("unimplemented interrupt routine: vector 1");
        }
        break;
        case 2:
        {
            //handle vector 2
            throw std::runtime_error("unimplemented interrupt routine: vector 2");
        }
        break;
        case 3:
        {
            //handle vector 3
            vm->debugOn = true;
        }
        break;
        case 4:
        {
            //handle vector 4
            throw std::runtime_error("unimplemented interrupt routine: vector 4");
        }
        break;
        case 5:
        {
            //handle vector 5
            throw std::runtime_error("unimplemented interrupt routine: vector 5");
        }
        break;
        case 6:
        {
            //handle vector 6
            throw std::runtime_error("unimplemented interrupt routine: vector 6");
        }
        break;
        case 7:
        {
            //handle vector 7
            throw std::runtime_error("unimplemented interrupt routine: vector 7");
        }
        break;
        case 8:
        {
            //handle vector 8
            throw std::runtime_error("unimplemented interrupt routine: vector 8");
        }
        break;
        case 9:
        {
            //handle vector 9
            handleNativeCall();
        }
        break;
        case 10:
        {
            //handle vector 10
            throw std::runtime_error("unimplemented interrupt routine: vector 10");
        }
        break;
        default: throw std::runtime_error("INSTRUCTION_SET: interrupt vector not handled.");
    }
}

} //namespace Logi
