//Logi includes
#include "../InstructionSet.h"

//// TEMP
#include <iostream>
using namespace std;

namespace Logi
{

void InstructionSet::INT() const
{
    //
}

void InstructionSet::DI() const
{
    //
}

void InstructionSet::EI() const
{
    //
}

void InstructionSet::HALT() const
{
    cout << "Got HALT instruction, shutting down the virtual machine..." << endl;
    exit(0);
}

void InstructionSet::NOP() const
{
    //
}

} //namespace Logi
