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
            throw std::runtime_error("unimplemented interrupt routine: vector 3");
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

//
// INTERRUPT    FUNCTION ($R1)  DESCRIPTION
// -------------------------------------------------------------
// 0            0               Opens a file
// 0            1               Closes a file
// 0            2               Flushes a file's buffer
// 0            3               Flushes the buffer to std::cin
// 0            4               Flushes the buffer to std::cout
// 0            5               Flushes the buffer to std::cerr
// 0            6               Moves the file position marker to the first byte in a file
// 0            7               Returns the current location of the file position marker
// 0            8               Sets the location of the file position marker
// 0            9               Tests for EOF
// 0            10              Tests for an I/O error
// 0            11              Reads bytes from a file
// 0            12              Writes bytes to a file
// 0            13              Reads bytes from std::cin
// 0            14              Writes bytes to std::cout
// 0            15              Writes bytes to std::cerr
// 0            16              Prints a character to std::cout
// 0            17              Prints a wide character to std::cout
// 0            18              Prints a string to std::cout
// 0            19              Prints a wide string to std::cout
// 0            20              Prints an integer to to std::cout
// 0            21              Prints a floating-point value to std::cout
// 0            22              Reads a string from std::cin
// 0            23              Reads a wide string from std::cin
// 0            24              Reads an integer from std::cin
// 0            25              Reads a floating-point value from std::cin
//
void InstructionSet::handleFileIO()
{
    //set console color
    std::cout << Console::GREEN;

    switch((U1)vm->registers.R($R1))
    {
        case 0:
        {
            cout << "opening file for writing..." << endl;

            const std::string& filename = "test.ASM";
            //const std::string& filename = (const char*)&(vm->registers.R($R4));

            file.open(filename,std::ios::in);

            if(!file.is_open())
            {
                // error
                vm->registers.R($R4) = 0;
            }
            else
            {
                // all good
                vm->registers.R($R4) = (U8)&file;
            }
        }
        break;
        case 1:
        {
            cout << "closing file..." << endl;

            file.close();
        }
        break;
        case 2:
        {
            cout << "flushing the file buffer..." << endl;

            file.flush();
        }
        break;
        case 3:
        {
            //
        }
        break;
        case 4:
        {
            //
        }
        break;
        case 5:
        {
            //
        }
        break;
        case 14:
        {
            //
        }
        break;
        case 16:
        {
            std::cout << (char)vm->registers.R($R2);
        }
        break;
        case 17:
        {
            //
        }
        break;
        case 18:
        {
            const char* c_ptr = (const char *)&(*vm->ram)(vm->registers.R($TOP));
            while(*c_ptr != '\0')
            {
                std::cout << *c_ptr;
                c_ptr--;
            }
        }
        break;
        case 20:
        {
            std::cout << std::dec << (S8)vm->registers.R($R2);
        }
    }

    std::cout << Console::RESET;
}

} //namespace Logi
