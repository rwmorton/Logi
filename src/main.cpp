#include <iostream>
#include <ostream>
#include <fstream>
#include <memory>
#include <fstream>
#include <iomanip>
#include <variant>
using namespace std;

//Logi includes
#include "Logi.h"

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
        vm.init(argc,argv);
        vm.run();
        vm.shutdown();
    }
    catch(const std::exception& e)
    {
        cout << e.what() << endl;
        vm.shutdown();
    }

    try
    {
        Logi::InstructionSet iset;
        cout << iset(Logi::LBI) << endl;
        cout << iset(Logi::FADD) << endl;
        cout << iset(Logi::MOV) << endl;
        cout << iset(Logi::BAD) << endl;
    }
    catch(const std::exception& e)
    {
        cout << e.what() << endl;
    }

    //
    //
    //
    using namespace Logi;
    U1 byte1;
    U1 byte2;
    U1 byte3;
    U1 byte4;

    U2 word = 256 + 1; // 0x10 0x01
    word = 4096 + 1; // 0x100 0x01

    cout << showbase << hex;
    std::ios_base::fmtflags hexStream(cout.flags());

    U1* ptr = (U1*)&word;
    byte1 = 0x10;
    byte2 = 0x01;

    cout << word << endl;
    cout << static_cast<U8>(byte1) << ' ' << static_cast<U8>(byte2) << endl;

    U4 dword = 268435456; // 0x10000000
    U4 dword2 = 4026531840; //0xf0000000
    U4 dword3 = 0xffffffff;

    cout << dword << endl;
    cout << dword2 << endl;
    cout << dword3 << endl;

    U4 dwordOut = dword3 + 1;
    cout << dwordOut << endl;

    U4 myDword = 0x1a2b3c4d;
    cout << myDword << endl;

    U1 myBytes[4]{};
    Transform::getInstance()->dwordToBytecode(myDword,myBytes);

    cout << static_cast<U8>(myBytes[0]) << ' '
        << static_cast<U8>(myBytes[1]) << ' '
        << static_cast<U8>(myBytes[2]) << ' '
        << static_cast<U8>(myBytes[3]) << endl;

    U1 THE_BYTE = 0x3f;
    cout << "TEST: " << static_cast<int>(THE_BYTE) << endl;

    cout << showbase << hex << static_cast<int>('x') << endl;

    Byte myByte(101);
    cout << myByte << endl;
    Byte newByte(myByte);
    cout << myByte << endl;

    UByte myUByte(33);
    cout << myUByte << endl;

    UByte newUByte(255);
    cout << newUByte << endl;
    cout << endl;
    cout << "BEFORE ASSIGNMENT: " << myUByte << endl;
    myUByte = newUByte;
    cout << "AFTER ASSIGNMENT: " << myUByte << endl;

    std::variant<int,float> v,w;
    v = 42;
    int i = std::get<int>(v);
    w = 101;

    cout << "testing += operator" << endl;
    UByte result(0);
    cout << result << endl;
    result += myUByte;
    cout << result << endl;
    result += newUByte;
    cout << result << endl;

    Byte A(1),B(4),C;
    cout << A << ' ' << B << ' ' << C << endl;
    C = A;
    cout << A << ' ' << B << ' ' << C << endl;
    C += B;
    cout << A << ' ' << B << ' ' << C << endl;

    cout << C << endl;
    cout << ++C << endl;
    cout << C << endl;
    cout << C++ << endl;
    cout << C << endl;

    return 0;
}
