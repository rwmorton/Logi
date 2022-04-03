//Logi includes
#include "Assembler.h"

//std includes
#include <fstream>
#include <iostream>

namespace Logi
{

const Flag Assembler::X_FLAG(Assembler::FlagID::X,{"-","xX"},1);
const Flag Assembler::Y_FLAG(Assembler::FlagID::Y,{"-","yY"},2);
const Flag Assembler::Z_FLAG(Assembler::FlagID::Z,{"-","zZ"},3);

Assembler::Assembler()
{
    addFlag(X_FLAG);
    addFlag(Y_FLAG);
    addFlag(Z_FLAG);
}

Assembler::~Assembler()
{
    //
}

//
// Load ASM file from command line args
//
void Assembler::load(int argc,char* argv[])
{
    std::cout << "parsing args...\n";

    std::vector<Flag> flags = parseArgs(argc,argv);

    std::cout << "parseArgs results:\n";
    std::cout << "Received " << flags.size() << " flags.\n";

    std::cout << "Filename = " << filename << std::endl;

    std::vector<Flag>::iterator flags_it = flags.begin();
    while(flags_it != flags.end())
    {
        switch(flags_it->getId())
        {
            case Assembler::FlagID::X:
            {
                std::cout << "got X flag:\n";
                //we expect it's only argument to be an integer
                int arg = std::stoi(flags_it->arg(0));
                std::cout << "\tit's argument is an integer = " << arg << std::endl;
            }
            break;
            case Assembler::FlagID::Y:
            {
                std::cout << "got Y flag:\n";
                //we expect it's first argument to be a double
                double arg1 = std::stod(flags_it->arg(0));
                std::cout << "\targ1 is a double = " << arg1 << std::endl;
                //and we expect it's second argument to be an integer
                double arg2 = std::stoi(flags_it->arg(1));
                std::cout << "\targ2 is an integer = " << arg2 << std::endl;
            }
            break;
            case Assembler::FlagID::Z:
            {
                std::cout << "got Z flag:\n";
                //char
                char arg1 = flags_it->arg(0).at(0);
                std::cout << "\targ1 is a char = " << arg1 << std::endl;
                std::string arg2 = flags_it->arg(1);
                std::cout << "\targ2 is a string = " << arg2 << std::endl;
                int arg3 = std::stoi(flags_it->arg(2));
                std::cout << "\targ3 is an integer = " << arg3 << std::endl;
            }
            break;
            default: break;
        }

        ++flags_it;
    }

    //load the asm file
    /*std::ifstream in(asmFile,std::ios::in | std::ios::binary);
    if(!in.is_open())
    {
        throw std::runtime_error("LOAD_ASM: could not load file.");
    }

    //
    // TODO
    //

    //all done, close the file stream
    in.close();*/
}

} //namespace Logi
