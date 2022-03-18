#include <iostream>
#include <memory>
using namespace std;

//Logi includes
#include "Logi.h"

int main(int argc,char *argv[])
{
    cout << "Testing Virtual Machine" << endl;

    Logi::VirtualMachine vm;

    const Logi::Stream* stream = Logi::Stream::getInstance();
    stream->U_REG("test",257);
    cout << endl;
    stream->U4(42);
    cout << endl;

    Logi::Bytecode bc;
    bc.load(argc,argv);

    return 0;
}
