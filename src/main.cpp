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

    char buf[9] = {'t','e','s','t','.','A','S','M','\0'};
    for(int i=0; i<9; i++)
    {
        cout << (int)buf[i] << endl;
    }

    char hello[10] = {'h','e','l','l','o','.','t','x','t','\0'};
    for(int i=0; i<10; i++)
    {
        cout << (int)hello[i] << endl;
    }

    char hi[8] = {'h','i',' ','b','r','o','!','\0'};
    for(int i=0; i<8; i++)
    {
        cout << (int)hi[i] << endl;
    }

    Logi::U1 file_buf[9] = {116,101,115,116,46,65,83,77,0};

    std::string file_str = (const char*)&file_buf;

    cout << "file_str = " << file_str << endl;

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
