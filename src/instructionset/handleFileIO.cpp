//Logi includes
#include "../InstructionSet.h"
#include "../VirtualMachine.h"
#include "../Console.h"

namespace Logi
{

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

    // get the value in $R1
    const U1 R1 = (U1)vm->registers.R($R1);

    switch(R1)
    {
        case 0:
        {
            //open the file at string in address stored in $R2
            const std::string& filename = (const char*)&(vm->registers.R($R2));
            file.open(filename,std::ios::in);
            //save result of opening file in $R2 (0 for failure, address of file otherwise)
            !file.is_open() ? vm->registers.R($R2) = 0 : vm->registers.R($R2) = (U8)&file;
        }
        break;
        case 1: file.close(); break;
        case 2: file.flush(); break;
        //
        // 3, 4, 5 omitted for now
        //
        case 6: file.seekg(0); break; // go to the first byte in the file
        case 7:
        {
            // save current file position in $R2
            const int pos = file.tellg();
            vm->registers.R($R2) = (S8)pos;
        }
        break;
        case 8:
        {
            // set the file position to the value in $R2
            // that is offset from the value in $R3
            //
            // $R3  LOC
            // 0    beginning of file
            // 1    end of file
            // 2    current position
            //
            const U1 R2 = vm->registers.R($R2);
            const U1 R3 = vm->registers.R($R3);

            switch(R3)
            {
                case 0: file.seekg(R2,std::ios_base::beg); break; // beginning of file
                case 1: file.seekg(R2,std::ios_base::end); break; // end of file
                case 2: file.seekg(R2,std::ios_base::cur); break; // current position
                default:
                {
                    std::string errorStr {"INSTRUCTION_SET: interrupt 0 function ("};
                    errorStr += std::to_string(R3);
                    errorStr += ") not handled.";
                    throw std::runtime_error(errorStr);
                }
            }
        }
        case 9:
        {
            // set $R2 to 1 if at eof, 0 otherwise
            vm->registers.R($R2) = file.eof() ? 1 : 0;
        }
        break;
        //
        // case 10 omitted for now
        //
        case 11:
        {
            // read bytes from a file
            // $R2 = number of bytes to read
            // $R3 = address of buffer to store data read in
            // $R4 = number of bytes actually read
            // $R5 = 0 if no error, 1 otherwise
            const U1 R2 = vm->registers.R($R2);
            const U8 R3 = vm->registers.R($R3);

            char buffer[R2];
            int bytesRead=0;
            while(bytesRead < R2)
            {
                if(file.eof())
                {
                    vm->registers.R($R4) = bytesRead; // number of bytes read
                    vm->registers.R($R5) = 1; // error
                    return;
                }
                buffer[bytesRead++] = file.get();
            }

            vm->registers.R($R4) = bytesRead; // number of bytes read
            vm->registers.R($R5) = 0; // success
        }
        break;
        //
        // case 12 omitted for now
        //
        case 13:
        {
            std::cout << "READY TO READ FROM STD::CIN: ";

            // read bytes from std::cin
            // $R2 = number of bytes to read
            // $R3 = address of buffer to store data read in
            // $R4 = number of bytes actually read
            // $R5 = 0 if no error, 1 otherwise
            const U8 R2 = vm->registers.R($R2);
            U8 R3 = vm->registers.R($R3);

            char buffer[R2];
            int bytesRead=0;
            while(bytesRead < R2)
            {
                buffer[bytesRead] = std::cin.get();

                if(std::cin.eof() || buffer[bytesRead] == '\n' || buffer[bytesRead] == '\r')
                {
                    vm->registers.R($R4) = bytesRead; // number of bytes read
                    vm->registers.R($R5) = 1; // error
                    return;
                }

                (*vm->ram)(R3) = buffer[bytesRead];

                bytesRead++;
                R3++;
            }

            vm->registers.R($R4) = bytesRead; // number of bytes read
            vm->registers.R($R5) = 0; // success
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
