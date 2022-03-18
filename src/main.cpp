#include <iostream>
#include <ostream>
#include <fstream>
#include <memory>
#include <fstream>
using namespace std;

//Logi includes
#include "Logi.h"

int main(int argc,char *argv[])
{
    ////////////////////////////////////////////////////////
    /////////////////// MAKE A TEST FILE ///////////////////
    ////////////////////////////////////////////////////////
    ofstream out("program.RUN",ios::binary|ios::out);
    Logi::U2 magic = 0xDEED;
    Logi::U8 symbolTableSize = 0x01;
    Logi::U8 stringTableSize = 0x02;
    Logi::U8 bytecodeSize = 0x80; //128
    
    Logi::U1 MAGIC[2]{};
    Logi::U1 SYMBOL[8]{};
    Logi::U1 STRING[8]{};
    Logi::U1 BYTECODE_SIZE[8]{};
    const Logi::Transform* transform = Logi::Transform::getInstance();
    transform->wordToBytecode(magic,MAGIC);
    transform->qwordToBytecode(symbolTableSize,SYMBOL);
    transform->qwordToBytecode(stringTableSize,STRING);
    transform->qwordToBytecode(bytecodeSize,BYTECODE_SIZE);

    Logi::Stream* stream = Logi::Stream::getInstance();
    stream->bytes(MAGIC,2);
    stream->bytes(SYMBOL,8);
    stream->bytes(STRING,8);
    stream->bytes(BYTECODE_SIZE,8);

    cout << endl << "MAGIC BYTES: ";
    stream->bytes(MAGIC,2);
    out.write((const char*)&magic,2);
    cout << endl;
    cout << "SYMBOL BYTES: ";
    stream->bytes(SYMBOL,8);
    out.write((const char*)&symbolTableSize,8);
    cout << endl;
    cout << "STRING BYTES: ";
    stream->bytes(STRING,8);
    out.write((const char*)&stringTableSize,8);
    cout << endl;
    cout << "BYTECODE SIZE BYTES: ";
    stream->bytes(BYTECODE_SIZE,8);
    out.write((const char *)&bytecodeSize,8);
    cout << endl << endl;

    for(int i=1; i<=128; i++)
    {
        out.put(i);
    }
    out.close();
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////

    std::ifstream infile("program.RUN",ios::in|ios::binary|ios::ate);
    int length = infile.tellg();
    infile.seekg(0); //go to beginning
    std::vector<Logi::U1> bytes{};
    Logi::U1 theByte{};
    while(!infile.eof())
    {
        theByte = infile.get();
        bytes.push_back(theByte);
        infile.peek();
    }
    infile.close();

    ////////////////////////////////////////////////////////
    //another test file - random stuff
    //make some program file
    symbolTableSize = 16;
    stringTableSize = 32;
    bytecodeSize = 1024;
    fstream out2("random.RUN",std::ios::binary|std::ios::out);
    out2.write((const char*)&magic,sizeof(Logi::U2));
    out2.write((const char*)&symbolTableSize,sizeof(Logi::U8));
    out2.write((const char*)&stringTableSize,sizeof(Logi::U8));
    out2.write((const char*)&bytecodeSize,sizeof(Logi::U8));
    //
    //write random symbols
    Logi::U1 byte{};
    for(int i=0; i<1024; i++)
    {
        out2.put(std::rand() % 255);
    }
    out2.close();
    ////////////////////////////////////////////////////////

    cout << "Testing Virtual Machine" << endl;
    cout << "-----------------------" << endl;

    try
    {
        Logi::VirtualMachine vm;
        vm.init(argc,argv);
        vm.run();
        vm.shutdown();
    }
    catch(const std::exception& e)
    {
        cout << e.what() << endl;
    }

    Logi::InstructionSet iset;
    cout << iset(Logi::LBI) << endl;
    cout << iset(Logi::FADD) << endl;
    cout << iset(Logi::BAD) << endl;

    return 0;
}
