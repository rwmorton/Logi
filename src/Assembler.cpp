//Logi includes
#include "Assembler.h"

//std includes
#include <fstream>
#include <iomanip>

namespace Logi
{

const Flag Assembler::DEBUG_FLAG(Assembler::FlagID::DEBUG,{"-","dD"},0);
const Flag Assembler::ALLOW_ERRORS_FLAG(Assembler::FlagID::ALLOW_ERRORS,{"-","eE"},1);
const Flag Assembler::CREATE_LISTING_FLAG(Assembler::FlagID::CREATE_LISTING,{"-","lL"},0);
const Flag Assembler::OUTPUT_FILE_FLAG(Assembler::FlagID::OUTPUT_FILE,{"-","oO"},1);

Assembler::Assembler() : omitDebug{false}, numErrors{0}, createListing{false}
{
    addFlag(DEBUG_FLAG);
    addFlag(ALLOW_ERRORS_FLAG);
    addFlag(CREATE_LISTING_FLAG);
    addFlag(OUTPUT_FILE_FLAG);
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
    std::vector<Flag> flags = parseArgs(argc,argv);

    std::vector<Flag>::iterator flags_it = flags.begin();
    while(flags_it != flags.end())
    {
        switch(flags_it->getId())
        {
            case Assembler::FlagID::DEBUG: omitDebug = true;
            break;
            case Assembler::FlagID::ALLOW_ERRORS: numErrors = std::stoi(flags_it->arg(0));
            break;
            case Assembler::FlagID::CREATE_LISTING: createListing = true;
            break;
            case Assembler::FlagID::OUTPUT_FILE: outputFile = flags_it->arg(0);
            break;
            default: throw std::runtime_error("ASSEMBLER: invalid flag id.");
        }

        ++flags_it;
    }

    //load the asm file
    std::ifstream in(filename,std::ios::in | std::ios::binary);
    if(!in.is_open())
    {
        throw std::runtime_error("LOAD_ASM: could not load file.");
    }

    //
    // TODO
    //

    //all done, close the file stream
    in.close();
}

std::ostream& operator<<(std::ostream& out,const Assembler& asmb)
{
    out << std::dec << "ASSEMBLER:\n";
    out << std::setw(11) << std::setfill('-') << '\n';
    out << "filename = " << asmb.filename << '\n';
    out << "allow num errors = " << asmb.numErrors << '\n';
    out << "omit debug? ";
    asmb.omitDebug ? out << "yes\n" : out << "no\n";
    out << "creating listing file? ";
    asmb.createListing ? out << "yes\n" : out << "no\n";
    out << "output file = " << asmb.outputFile << '\n';
    return out;
}

} //namespace Logi
