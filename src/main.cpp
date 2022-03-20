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

//Logi includes
#include "Logi.h"

#include "Testing.h"

void makeRandomBytecodeFile()
{
    std::ofstream out("random.RUN",std::ios::binary|std::ios::out);
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

    std::cout << "Testing Virtual Machine\n" << std::setw(25) << std::setfill('-') << '\n';

    Logi::VirtualMachine vm;

    try
    {
        vm.init(argc,argv);
        //vm.run();
        //vm.shutdown();
    }
    catch(const std::exception& e)
    {
        std::cout << "ERROR: " << e.what() << std::endl;
        vm.shutdown();
    }

    return 0;
}
