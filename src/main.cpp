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

int main(int argc,char *argv[])
{
    //Logi::makeRandomBytecodeFile();

    std::cout << "Testing Virtual Machine\n" << std::setw(25) << std::setfill('-') << '\n';

    Logi::VirtualMachine vm;

    try
    {
        vm.init(argc,argv);
        vm.run();
        vm.shutdown();
    }
    catch(const std::exception& e)
    {
        std::cout << "ERROR: " << e.what() << std::endl;
        vm.shutdown();
    }

    Logi::Transform::checkEndian(); //FORCE LINKER TO WORK

    return 0;
}
