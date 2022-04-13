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

    std::string str {"this is a test string that is the virtual machine is printing to std::cout"};
    const char *str_p = str.c_str();
    cout << "BYTECODE:" << endl;
    cout << endl;
    cout << ".GB string " << str.length() + 1<< std::endl;
    cout << "\n# allocate space for string\n";
    cout << "LQI $R3 " << str.length() + 1<< std::endl;
    cout << "SUB $SP $SP $R3\n";
    cout << "\n# push bytes from string\n";
    for(int i=0; i<str.length(); i++)
    {
        cout << "LBI $R1 " << (int)*str_p << '\n';
        cout << "PUSHB $R1\n";
        cout << std::endl;
        str_p++;
    }
    str_p = nullptr;

    // add end of string
    cout << "LBI $R1 " << (int)0 << '\n';
    cout << "PUSHB $R1\n";

    cout << endl;

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
