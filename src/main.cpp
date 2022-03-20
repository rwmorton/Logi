#include <iostream>
#include <ostream>
#include <fstream>
#include <memory>
#include <fstream>
#include <iomanip>
#include <variant>
#include <initializer_list>
#include <memory>
#include <algorithm>
using namespace std;

//Logi includes
#include "Logi.h"

#include "Testing.h"

void makeRandomBytecodeFile()
{
    ofstream out("random.RUN",ios::binary|ios::out);
    Logi::U2 magic = 0xDEED;
    Logi::U8 symbolTableSize = 16;
    Logi::U8 stringTableSize = 64;
    Logi::U8 bytecodeSize = 1024;

    out.write((const char*)&magic,sizeof(Logi::U2));
    out.write((const char*)&symbolTableSize,sizeof(Logi::U8));
    out.write((const char*)&stringTableSize,sizeof(Logi::U8));
    out.write((const char*)&bytecodeSize,sizeof(Logi::U8));
    
    //write random bytes
    Logi::U1 byte{};
    for(int i=0; i<bytecodeSize; i++)
    {
        out.put(std::rand() % 255);
    }
    out.close();
}

int main(int argc,char *argv[])
{
    //makeRandomBytecodeFile();

    cout << "Testing Virtual Machine" << endl;
    cout << "-----------------------" << endl;

    Logi::VirtualMachine vm;

    try
    {
        //vm.init(argc,argv);
        //vm.run();
        //vm.shutdown();
    }
    catch(const std::exception& e)
    {
        cout << e.what() << endl;
        vm.shutdown();
    }

    try
    {
        const Logi::InstructionSet* iset = Logi::InstructionSet::getInstance();
        cout << (*iset)(Logi::LBI) << endl;
        cout << (*iset)(Logi::FADD) << endl;
        cout << (*iset)(Logi::MOV) << endl;
        cout << (*iset)(Logi::BAD) << endl;
    }
    catch(const std::exception& e)
    {
        cout << e.what() << endl;
    }

    ////////////////////////////////////////////////////////

    int res = Logi::Transform::getInstance()->checkEndian();
    switch(res)
    {
        case Logi::Endian::BIG:
        {
            cout << "Platform is big endian" << endl;
        }
        break;
        case Logi::Endian::LITTLE:
        {
            cout << "Platform is little endian" << endl;
        }
        break;
    }

    return 0;
}
