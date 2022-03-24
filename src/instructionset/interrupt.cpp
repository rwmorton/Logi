//Logi includes
#include "../InstructionSet.h"

//// TEMP
#include <iostream>
using namespace std;

namespace Logi
{

//
// Accepts an integer argument (the interrupt vector) which
// is an inde into one of the virtual machines iterrupt service
// routines. A switch statement is used to redirect the virtual
// machines execution path to the appropriate service routine.
//
void InstructionSet::handleInterrupt(U1 byte) const
{
    if(!interruptOn) return; //interrupts are disabled

    switch(byte)
    {
        case 0:
        {
            //handle vector 0
            throw std::runtime_error("unimplemented interrupt routine: vector 0");
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
            throw std::runtime_error("unimplemented interrupt routine: vector 3");
            //
            // DEBUG = TRUE
            //
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
            throw std::runtime_error("unimplemented interrupt routine: vector 9");
        }
        break;
        case 10:
        {
            //handle vector 10
            throw std::runtime_error("unimplemented interrupt routine: vector 10");
        }
        break;
        default: throw std::runtime_error("interrupt vector not handled.");
    }
}

} //namespace Logi
