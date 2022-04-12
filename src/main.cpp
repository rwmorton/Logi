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

int main(const int argc,const char *argv[])
{
    //Logi::makeRandomBytecodeFile();

    #ifdef __LOGI_TESTS_ON__
        std::cout << "Testing Virtual Machine\n" << std::setw(25) << std::setfill('-') << '\n';
        Logi::run_all_tests();
    #endif

    Logi::VirtualMachine vm;

    bool runAssembler = true;

    try
    {
        if(runAssembler)
        {
            //run Assembler
            Logi::Assembler* file = new Logi::Assembler();
            file->load(argc,argv);
            std::cout << *file << std::endl;
            file->save();
            delete file;
        }

        //vm.init(argc,argv);

        //override for testing
        int argc_override = 3;
        const char* arg1 = "./build/src/main";
        const char* arg2 = "-d";
        const char* arg3 = "/home/richard/work/projects/Logi/test.RUN";
        const char* argv_override[] = {arg1,arg2,arg3};
        vm.init(argc_override,argv_override);

        vm.run();
        vm.shutdown();
    }
    catch(const std::exception& e)
    {
        std::cout << "ERROR: " << e.what() << std::endl;
        vm.shutdown();
    }

    return 0;
}
