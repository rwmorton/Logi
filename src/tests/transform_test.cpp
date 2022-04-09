//Logi includes
#include "../Transform.h"
#include "../Stream.h"

//std includes
#include <cassert>

namespace Logi
{

#ifdef __LOGI_TESTS_ON__

std::ostream& out = Stream::getInstance()->get();
//
// these bytes are stored in big-endian format.
//
U1 bytes[8] = {0x12,0xAB,0x34,0xCD,0x56,0xEF,0x78,0xCA};

void Transform::TEST_setPlatform(const Endian end)
{
    out << "SETTING TEST PLATFORM TO ";
    end == Endian::LITTLE ? out << "LITTLE" : out << "BIG";
    out << "-ENDIAN\n";
    PLATFORM = end;
}

void Transform::TEST_run_all_tests()
{
    out << "RUNNING TRANSFORM TESTS...\n";
    
    //run tests in little-endian platform
    Transform::TEST_setPlatform(Endian::LITTLE);
    TEST_bytecodeToXYZ();
    TEST_xyzToBytecode();

    //run tests in big-endian platform
    Transform::TEST_setPlatform(Endian::BIG);
    TEST_bytecodeToXYZ();
    TEST_xyzToBytecode();

    //reset to system platform
    out << "RESETTING TO SYSTEM PLATFORM...\n";
    Transform::setPlatform();

    //not dependent on byte ordering
    TEST_xyzToRegister();
    TEST_xyzToStack();
    TEST_xyzFromStack();
    //TEST_xyz_bigToLittleEndian();
}

void Transform::TEST_bytecodeToXYZ()
{
    out << "TEST_bytecodeToXYZ() running:\n";

    //bytecode to word
    U2 u2_res = bytecodeToWord((U1*)&bytes);
    U1* buffer = (U1*)&u2_res;
    if(Transform::PLATFORM == Endian::LITTLE)
    {
        assert(*(&buffer[0]) == 0xAB);
        assert(*(&buffer[1]) == 0x12);
    }
    else
    {
        assert(*(&buffer[0]) == 0x12);
        assert(*(&buffer[1]) == 0xAB);
    }
    out << "\tbytecode-to-word test passed!\n";

    //bytecode to dword
    U4 u4_res = bytecodeToDWord((U1*)&bytes);
    buffer = (U1*)&u4_res;
    if(Transform::PLATFORM == Endian::LITTLE)
    {
        assert(*(&buffer[0]) == 0xCD);
        assert(*(&buffer[1]) == 0x34);
        assert(*(&buffer[2]) == 0xAB);
        assert(*(&buffer[3]) == 0x12);
    }
    else
    {
        assert(*(&buffer[0]) == 0x12);
        assert(*(&buffer[1]) == 0xAB);
        assert(*(&buffer[2]) == 0x34);
        assert(*(&buffer[3]) == 0xCD);
    }
    out << "\tbytecode-to-dword test passed!\n";

    //bytecode to qword
    U8 u8_res = bytecodeToQWord((U1*)&bytes);
    buffer = (U1*)&u8_res;
    if(Transform::PLATFORM == Endian::LITTLE)
    {
        assert(*(&buffer[0]) == 0xCA);
        assert(*(&buffer[1]) == 0x78);
        assert(*(&buffer[2]) == 0xEF);
        assert(*(&buffer[3]) == 0x56);
        assert(*(&buffer[4]) == 0xCD);
        assert(*(&buffer[5]) == 0x34);
        assert(*(&buffer[6]) == 0xAB);
        assert(*(&buffer[7]) == 0x12);
    }
    else
    {
        assert(*(&buffer[0]) == 0x12);
        assert(*(&buffer[1]) == 0xAB);
        assert(*(&buffer[2]) == 0x34);
        assert(*(&buffer[3]) == 0xCD);
        assert(*(&buffer[4]) == 0x56);
        assert(*(&buffer[5]) == 0xEF);
        assert(*(&buffer[6]) == 0x78);
        assert(*(&buffer[7]) == 0xCA);
    }
    out << "\tbytecode-to-qword test passed!\n";

    //bytecode to float
    F4 f4_res = bytecodeToFloat((U1*)&bytes);
    buffer = (U1*)&f4_res;
    if(Transform::PLATFORM == Endian::LITTLE)
    {
        assert(*(&buffer[0]) == 0xCD);
        assert(*(&buffer[1]) == 0x34);
        assert(*(&buffer[2]) == 0xAB);
        assert(*(&buffer[3]) == 0x12);
    }
    else
    {
        assert(*(&buffer[0]) == 0x12);
        assert(*(&buffer[1]) == 0xAB);
        assert(*(&buffer[2]) == 0x34);
        assert(*(&buffer[3]) == 0xCD);
    }
    out << "\tbytecode-to-float test passed!\n";

    //bytecode to double
    F8 f8_res = bytecodeToDouble((U1*)&bytes);
    buffer = (U1*)&f8_res;
    if(Transform::PLATFORM == Endian::LITTLE)
    {
        assert(*(&buffer[0]) == 0xCA);
        assert(*(&buffer[1]) == 0x78);
        assert(*(&buffer[2]) == 0xEF);
        assert(*(&buffer[3]) == 0x56);
        assert(*(&buffer[4]) == 0xCD);
        assert(*(&buffer[5]) == 0x34);
        assert(*(&buffer[6]) == 0xAB);
        assert(*(&buffer[7]) == 0x12);
    }
    else
    {
        assert(*(&buffer[0]) == 0x12);
        assert(*(&buffer[1]) == 0xAB);
        assert(*(&buffer[2]) == 0x34);
        assert(*(&buffer[3]) == 0xCD);
        assert(*(&buffer[4]) == 0x56);
        assert(*(&buffer[5]) == 0xEF);
        assert(*(&buffer[6]) == 0x78);
        assert(*(&buffer[7]) == 0xCA);
    }
    out << "\tbytecode-to-qword test passed!\n";

    out << "TEST_bytecodeToXYZ() 5 tests passed!\n";
}

void Transform::TEST_xyzToBytecode()
{
    //U1 bytes[8] = {0x12,0xAB,0x34,0xCD,0x56,0xEF,0x78,0xCA};
    out << "TEST_xyzToBytecode() running:\n";

    //word to bytecode
    U2 word;
    U1* buffer = (U1*)&word;
    *(&buffer[0]) = 0x3F;
    *(&buffer[1]) = 0xA7;

    U1 word_bytes[2];
    wordToBytecode(word,word_bytes);
    if(Transform::PLATFORM == Endian::LITTLE)
    {
        assert(*(&word_bytes[0]) == 0xA7);
        assert(*(&word_bytes[1]) == 0x3F);
    }
    else
    {
        assert(*(&word_bytes[0]) == 0x3F);
        assert(*(&word_bytes[1]) == 0xA7);
    }
    out << "\tword-to-bytecode test passed!\n";

    //dword to bytecode
    U4 dword;
    buffer = (U1*)&dword;
    *(&buffer[0]) = 0x1A;
    *(&buffer[1]) = 0xE3;
    *(&buffer[2]) = 0x59;
    *(&buffer[3]) = 0xF3;

    U1 dword_bytes[4];
    dwordToBytecode(dword,dword_bytes);
    if(Transform::PLATFORM == Endian::LITTLE)
    {
        assert(*(&dword_bytes[0]) == 0xF3);
        assert(*(&dword_bytes[1]) == 0x59);
        assert(*(&dword_bytes[2]) == 0xE3);
        assert(*(&dword_bytes[3]) == 0x1A);
    }
    else
    {
        assert(*(&dword_bytes[0]) == 0x1A);
        assert(*(&dword_bytes[1]) == 0xE3);
        assert(*(&dword_bytes[2]) == 0x59);
        assert(*(&dword_bytes[3]) == 0xF3);
    }
    out << "\tdword-to-bytecode test passed!\n";

    //qword to bytecode
    U8 qword;
    buffer = (U1*)&qword;
    *(&buffer[0]) = 0xEC;
    *(&buffer[1]) = 0x37;
    *(&buffer[2]) = 0x9B;
    *(&buffer[3]) = 0xA3;
    *(&buffer[4]) = 0x15;
    *(&buffer[5]) = 0xBD;
    *(&buffer[6]) = 0x78;
    *(&buffer[7]) = 0xF6;

    U1 qword_bytes[4];
    qwordToBytecode(qword,qword_bytes);
    if(Transform::PLATFORM == Endian::LITTLE)
    {
        assert(*(&qword_bytes[0]) == 0xF6);
        assert(*(&qword_bytes[1]) == 0x78);
        assert(*(&qword_bytes[2]) == 0xBD);
        assert(*(&qword_bytes[3]) == 0x15);
        assert(*(&qword_bytes[4]) == 0xA3);
        assert(*(&qword_bytes[5]) == 0x9B);
        assert(*(&qword_bytes[6]) == 0x37);
        assert(*(&qword_bytes[7]) == 0xEC);
    }
    else
    {
        assert(*(&qword_bytes[0]) == 0xEC);
        assert(*(&qword_bytes[1]) == 0x37);
        assert(*(&qword_bytes[2]) == 0x9B);
        assert(*(&qword_bytes[3]) == 0xA3);
        assert(*(&qword_bytes[4]) == 0x15);
        assert(*(&qword_bytes[5]) == 0xBD);
        assert(*(&qword_bytes[6]) == 0x78);
        assert(*(&qword_bytes[7]) == 0xF6);
    }
    out << "\tqword-to-bytecode test passed!\n";

    //float to bytecode
    F4 float_;
    buffer = (U1*)&float_;
    *(&buffer[0]) = 0x91;
    *(&buffer[1]) = 0xAD;
    *(&buffer[2]) = 0x37;
    *(&buffer[3]) = 0xBF;

    U1 float_bytes[4];
    floatToBytecode(float_,float_bytes);
    if(Transform::PLATFORM == Endian::LITTLE)
    {
        assert(*(&float_bytes[0]) == 0xBF);
        assert(*(&float_bytes[1]) == 0x37);
        assert(*(&float_bytes[2]) == 0xAD);
        assert(*(&float_bytes[3]) == 0x91);
    }
    else
    {
        assert(*(&float_bytes[0]) == 0x91);
        assert(*(&float_bytes[1]) == 0xAD);
        assert(*(&float_bytes[2]) == 0x37);
        assert(*(&float_bytes[3]) == 0xBF);
    }
    out << "\tfloat-to-bytecode test passed!\n";

    //double to bytecode
    F8 double_;
    buffer = (U1*)&double_;
    *(&buffer[0]) = 0x1A;
    *(&buffer[1]) = 0x2B;
    *(&buffer[2]) = 0x3C;
    *(&buffer[3]) = 0x4D;
    *(&buffer[4]) = 0x5E;
    *(&buffer[5]) = 0x6F;
    *(&buffer[6]) = 0x7A;
    *(&buffer[7]) = 0x8B;

    U1 double_bytes[8];
    doubleToBytecode(double_,double_bytes);
    if(Transform::PLATFORM == Endian::LITTLE)
    {
        assert(*(&double_bytes[0]) == 0x8B);
        assert(*(&double_bytes[1]) == 0x7A);
        assert(*(&double_bytes[2]) == 0x6F);
        assert(*(&double_bytes[3]) == 0x5E);
        assert(*(&double_bytes[4]) == 0x4D);
        assert(*(&double_bytes[5]) == 0x3C);
        assert(*(&double_bytes[6]) == 0x2B);
        assert(*(&double_bytes[7]) == 0x1A);
    }
    else
    {
        assert(*(&double_bytes[0]) == 0x1A);
        assert(*(&double_bytes[1]) == 0x2B);
        assert(*(&double_bytes[2]) == 0x3C);
        assert(*(&double_bytes[3]) == 0x4D);
        assert(*(&double_bytes[4]) == 0x5E);
        assert(*(&double_bytes[5]) == 0x6F);
        assert(*(&double_bytes[6]) == 0x7A);
        assert(*(&double_bytes[7]) == 0x8B);
    }
    out << "\tdouble-to-bytecode test passed!\n";

    out << "TEST_xyzToBytecode() 5 tests passed!\n";
}

void Transform::TEST_xyzToRegister()
{
    out << "TEST_xyzToRegister() running:\n";

    U8 reg;
    U1* reg_buffer = (U1*)&reg;

    //byte to register
    U1 byte = 0xB3;
    Transform::byteToRegister(byte,reg);
    
    assert(*(&reg_buffer[0]) == 0xB3);
    assert(*(&reg_buffer[1]) == 0);
    assert(*(&reg_buffer[2]) == 0);
    assert(*(&reg_buffer[3]) == 0);
    assert(*(&reg_buffer[4]) == 0);
    assert(*(&reg_buffer[5]) == 0);
    assert(*(&reg_buffer[6]) == 0);
    assert(*(&reg_buffer[7]) == 0);
    out << "\tbyte-to-register test passed!\n";

    //word to register
    U2 word;
    U1* word_buffer = (U1*)&word;
    word_buffer[0] = 0xB3;
    word_buffer[1] = 0x1E;
    Transform::wordToRegister(word_buffer,reg);

    assert(*(&reg_buffer[0]) == 0xB3);
    assert(*(&reg_buffer[1]) == 0x1E);
    assert(*(&reg_buffer[3]) == 0);
    assert(*(&reg_buffer[4]) == 0);
    assert(*(&reg_buffer[5]) == 0);
    assert(*(&reg_buffer[6]) == 0);
    assert(*(&reg_buffer[7]) == 0);
    out << "\tword-to-register test passed!\n";

    //dword to register
    U4 dword;
    U1* dword_buffer = (U1*)&dword;
    dword_buffer[0] = 0xAB;
    dword_buffer[1] = 0x12;
    dword_buffer[2] = 0xCD;
    dword_buffer[3] = 0x34;
    Transform::dwordToRegister(dword_buffer,reg);

    assert(*(&reg_buffer[0]) == 0xAB);
    assert(*(&reg_buffer[1]) == 0x12);
    assert(*(&reg_buffer[2]) == 0xCD);
    assert(*(&reg_buffer[3]) == 0x34);
    assert(*(&reg_buffer[4]) == 0);
    assert(*(&reg_buffer[5]) == 0);
    assert(*(&reg_buffer[6]) == 0);
    assert(*(&reg_buffer[7]) == 0);
    out << "\tdword-to-register test passed!\n";

    //qword to register
    U8 qword;
    U1* qword_buffer = (U1*)&qword;
    qword_buffer[0] = 0x12;
    qword_buffer[1] = 0xAB;
    qword_buffer[2] = 0x34;
    qword_buffer[3] = 0xCD;
    qword_buffer[4] = 0x56;
    qword_buffer[5] = 0xEF;
    qword_buffer[6] = 0x78;
    qword_buffer[7] = 0xA1;
    Transform::qwordToRegister(qword_buffer,reg);

    assert(*(&reg_buffer[0]) == 0x12);
    assert(*(&reg_buffer[1]) == 0xAB);
    assert(*(&reg_buffer[2]) == 0x34);
    assert(*(&reg_buffer[3]) == 0xCD);
    assert(*(&reg_buffer[4]) == 0x56);
    assert(*(&reg_buffer[5]) == 0xEF);
    assert(*(&reg_buffer[6]) == 0x78);
    assert(*(&reg_buffer[7]) == 0xA1);
    out << "\tqword-to-register test passed!\n";

    //float to register
    F4 freg;
    U1* freg_buffer = (U1*)&freg;
    F4 float_;
    U1* float_buffer = (U1*)&float_;
    float_buffer[0] = 0x12;
    float_buffer[1] = 0x34;
    float_buffer[2] = 0x56;
    float_buffer[3] = 0x78;
    Transform::floatToRegister(float_buffer,freg);

    assert(*(&freg_buffer[0]) == 0x12);
    assert(*(&freg_buffer[1]) == 0x34);
    assert(*(&freg_buffer[2]) == 0x56);
    assert(*(&freg_buffer[3]) == 0x78);
    out << "\tfloat-to-register test passed!\n";

    //double to register
    F8 dreg;
    U1* dreg_buffer = (U1*)&dreg;
    F8 double_;
    U1* double_buffer = (U1*)&double_;
    double_buffer[0] = 0x12;
    double_buffer[1] = 0x34;
    double_buffer[2] = 0x56;
    double_buffer[3] = 0x78;
    double_buffer[4] = 0xAB;
    double_buffer[5] = 0xCD;
    double_buffer[6] = 0xEF;
    double_buffer[7] = 0xA7;
    Transform::doubleToRegister(double_buffer,dreg);

    assert(*(&dreg_buffer[0]) == 0x12);
    assert(*(&dreg_buffer[1]) == 0x34);
    assert(*(&dreg_buffer[2]) == 0x56);
    assert(*(&dreg_buffer[3]) == 0x78);
    assert(*(&dreg_buffer[4]) == 0xAB);
    assert(*(&dreg_buffer[5]) == 0xCD);
    assert(*(&dreg_buffer[6]) == 0xEF);
    assert(*(&dreg_buffer[7]) == 0xA7);
    out << "\tdouble-to-register test passed!\n";

    //qword to register
    U8 addr;
    U1* addr_buffer = (U1*)&qword;
    addr_buffer[0] = 0x1A;
    addr_buffer[1] = 0xB2;
    addr_buffer[2] = 0x3C;
    addr_buffer[3] = 0xD4;
    addr_buffer[4] = 0x5E;
    addr_buffer[5] = 0xF6;
    addr_buffer[6] = 0x1E;
    addr_buffer[7] = 0xD2;
    Transform::addressToRegister(addr_buffer,reg);

    assert(*(&reg_buffer[0]) == 0x1A);
    assert(*(&reg_buffer[1]) == 0xB2);
    assert(*(&reg_buffer[2]) == 0x3C);
    assert(*(&reg_buffer[3]) == 0xD4);
    assert(*(&reg_buffer[4]) == 0x5E);
    assert(*(&reg_buffer[5]) == 0xF6);
    assert(*(&reg_buffer[6]) == 0x1E);
    assert(*(&reg_buffer[7]) == 0xD2);
    out << "\taddress-to-register test passed!\n";

    out << "TEST_xyzToRegister() 7 tests passed!\n";
}

//
// construct a test "stack"
//
void set_test_stack(U1* stack)
{
    stack[0] = 0x00;
    stack[1] = 0x01;
    stack[2] = 0x02;
    stack[3] = 0x03;
    stack[4] = 0x04;
    stack[5] = 0x05;
    stack[6] = 0x06;
    stack[7] = 0x07;
    stack[8] = 0x08;
    stack[9] = 0x09;
    stack[10] = 0x0a;
    stack[11] = 0x0b;
    stack[12] = 0x0c;
    stack[13] = 0x0d;
    stack[14] = 0x0e;
    stack[15] = 0x0f;
}

void assert_initial_stack(U1 stack[16])
{
    assert(stack[0] == 0x00);
    assert(stack[1] == 0x01);
    assert(stack[2] == 0x02);
    assert(stack[3] == 0x03);
    assert(stack[4] == 0x04);
    assert(stack[5] == 0x05);
    assert(stack[6] == 0x06);
    assert(stack[7] == 0x07);
    assert(stack[8] == 0x08);
    assert(stack[9] == 0x09);
    assert(stack[10] == 0x0a);
    assert(stack[11] == 0x0b);
    assert(stack[12] == 0x0c);
    assert(stack[13] == 0x0d);
    assert(stack[14] == 0x0e);
    assert(stack[15] == 0x0f);
}

void Transform::TEST_xyzToStack()
{
    out << "TEST_xyzToStack() running:\n";

    //test stack
    U1 stack[16];
    U1* stackTop = &stack[15];

    //byte to stack test
    //set initial stack
    set_test_stack(stack);
    assert_initial_stack(stack);

    assert(*stackTop == 0x0f);
    U1 byte = 0xAD;
    Transform::byteToStack(byte,stackTop);
    assert(*stackTop == 0xAD);
    *stackTop = 0x0f;
    assert_initial_stack(stack);
    out << "\tbyte-to-stack test passed!\n";

    //word to stack test
    //reset initial stack
    set_test_stack(stack);
    assert_initial_stack(stack);

    assert(*stackTop == 0x0f);
    U2 word;
    U1* buffer = (U1*)&word;
    buffer[0] = 0x7C;
    buffer[1] = 0x5A;
    Transform::wordToStack(word,stackTop);
    assert(*stackTop == 0x7C);
    assert(*(&stack[14]) == 0x5A);
    out << "\tword-to-stack test passed!\n";

    //dword to stack test
    //reset initial stack
    set_test_stack(stack);
    assert_initial_stack(stack);

    assert(*stackTop == 0x0f);
    U4 dword;
    buffer = (U1*)&dword;
    buffer[0] = 0x98;
    buffer[1] = 0xAB;
    buffer[2] = 0x76;
    buffer[3] = 0xCD;
    Transform::dwordToStack(dword,stackTop);
    assert(*stackTop == 0x98);
    assert(*(&stack[14]) == 0xAB);
    assert(*(&stack[13]) == 0x76);
    assert(*(&stack[12]) == 0xCD);
    out << "\tdword-to-stack test passed!\n";

    //qword to stack test
    //reset initial stack
    set_test_stack(stack);
    assert_initial_stack(stack);

    assert(*stackTop == 0x0f);
    U8 qword;
    buffer = (U1*)&qword;
    buffer[0] = 0x12;
    buffer[1] = 0x34;
    buffer[2] = 0x56;
    buffer[3] = 0x78;
    buffer[4] = 0x9A;
    buffer[5] = 0xBC;
    buffer[6] = 0xDE;
    buffer[7] = 0xF1;
    Transform::qwordToStack(qword,stackTop);
    assert(*stackTop == 0x12);
    assert(*(&stack[14]) == 0x34);
    assert(*(&stack[13]) == 0x56);
    assert(*(&stack[12]) == 0x78);
    assert(*(&stack[11]) == 0x9A);
    assert(*(&stack[10]) == 0xBC);
    assert(*(&stack[9]) == 0xDE);
    assert(*(&stack[8]) == 0xF1);
    out << "\tqword-to-stack test passed!\n";

    //float to stack test
    //reset initial stack
    set_test_stack(stack);
    assert_initial_stack(stack);

    assert(*stackTop == 0x0f);
    F4 float_;
    buffer = (U1*)&float_;
    buffer[0] = 0x12;
    buffer[1] = 0xAB;
    buffer[2] = 0x34;
    buffer[3] = 0xCD;
    Transform::floatToStack(float_,stackTop);
    assert(*stackTop == 0x12);
    assert(*(&stack[14]) == 0xAB);
    assert(*(&stack[13]) == 0x34);
    assert(*(&stack[12]) == 0xCD);
    out << "\tfloat-to-stack test passed!\n";

    //double to stack test
    //reset initial stack
    set_test_stack(stack);
    assert_initial_stack(stack);

    assert(*stackTop == 0x0f);
    F8 double_;
    buffer = (U1*)&double_;
    buffer[0] = 0x1A;
    buffer[1] = 0xB2;
    buffer[2] = 0x3C;
    buffer[3] = 0xD4;
    buffer[4] = 0x5E;
    buffer[5] = 0xF6;
    buffer[6] = 0x7A;
    buffer[7] = 0xB8;
    Transform::doubleToStack(double_,stackTop);
    assert(*stackTop == 0x1A);
    assert(*(&stack[14]) == 0xB2);
    assert(*(&stack[13]) == 0x3C);
    assert(*(&stack[12]) == 0xD4);
    assert(*(&stack[11]) == 0x5E);
    assert(*(&stack[10]) == 0xF6);
    assert(*(&stack[9]) == 0x7A);
    assert(*(&stack[8]) == 0xB8);
    out << "\tdouble-to-stack test passed!\n";

    out << "TEST_xyzToStack() 6 tests passed!\n";
}

void Transform::TEST_xyzFromStack()
{
    out << "TEST_xyzFromStack() running:\n";

    //test stack
    U1 stack[16];
    U1* stackTop = &stack[15];
    U8 byte;
    U1* buffer = (U1*)&byte;

    //byte from stack test
    //set initial stack
    set_test_stack(stack);
    assert_initial_stack(stack);

    Transform::byteFromStack(byte,stackTop);
    assert(*(&buffer[0]) == stack[15]);
    assert(*(&buffer[1]) == 0);
    assert(*(&buffer[2]) == 0);
    assert(*(&buffer[3]) == 0);
    assert(*(&buffer[4]) == 0);
    assert(*(&buffer[5]) == 0);
    assert(*(&buffer[6]) == 0);
    assert(*(&buffer[7]) == 0);
    out << "\tbyte-from-stack test passed!\n";

    //byte from stack test
    //set initial stack
    set_test_stack(stack);
    assert_initial_stack(stack);

    Transform::wordFromStack(byte,stackTop);
    assert(*(&buffer[0]) == stack[15]);
    assert(*(&buffer[1]) == stack[14]);
    assert(*(&buffer[2]) == 0);
    assert(*(&buffer[3]) == 0);
    assert(*(&buffer[4]) == 0);
    assert(*(&buffer[5]) == 0);
    assert(*(&buffer[6]) == 0);
    assert(*(&buffer[7]) == 0);
    out << "\tword-from-stack test passed!\n";

    //byte from stack test
    //set initial stack
    set_test_stack(stack);
    assert_initial_stack(stack);

    Transform::dwordFromStack(byte,stackTop);
    assert(*(&buffer[0]) == stack[15]);
    assert(*(&buffer[1]) == stack[14]);
    assert(*(&buffer[2]) == stack[13]);
    assert(*(&buffer[3]) == stack[12]);
    assert(*(&buffer[4]) == 0);
    assert(*(&buffer[5]) == 0);
    assert(*(&buffer[6]) == 0);
    assert(*(&buffer[7]) == 0);
    out << "\tdword-from-stack test passed!\n";

    //byte from stack test
    //set initial stack
    set_test_stack(stack);
    assert_initial_stack(stack);

    Transform::qwordFromStack(byte,stackTop);
    assert(*(&buffer[0]) == stack[15]);
    assert(*(&buffer[1]) == stack[14]);
    assert(*(&buffer[2]) == stack[13]);
    assert(*(&buffer[3]) == stack[12]);
    assert(*(&buffer[4]) == stack[11]);
    assert(*(&buffer[5]) == stack[10]);
    assert(*(&buffer[6]) == stack[9]);
    assert(*(&buffer[7]) == stack[8]);
    out << "\tqword-from-stack test passed!\n";

    //float from stack test
    //set initial stack
    F4 float_;
    buffer = (U1*)&float_;
    set_test_stack(stack);
    assert_initial_stack(stack);

    Transform::floatFromStack(float_,stackTop);
    assert(*(&buffer[0]) == stack[15]);
    assert(*(&buffer[1]) == stack[14]);
    assert(*(&buffer[2]) == stack[13]);
    assert(*(&buffer[3]) == stack[12]);
    out << "\tfloat-from-stack test passed!\n";

    //double from stack test
    //set initial stack
    F8 double_;
    buffer = (U1*)&double_;
    set_test_stack(stack);
    assert_initial_stack(stack);

    Transform::doubleFromStack(double_,stackTop);
    assert(*(&buffer[0]) == stack[15]);
    assert(*(&buffer[1]) == stack[14]);
    assert(*(&buffer[2]) == stack[13]);
    assert(*(&buffer[3]) == stack[12]);
    assert(*(&buffer[4]) == stack[11]);
    assert(*(&buffer[5]) == stack[10]);
    assert(*(&buffer[6]) == stack[9]);
    assert(*(&buffer[7]) == stack[8]);
    out << "\tdouble-from-stack test passed!\n";

    out << "TEST_xyzFromStack() 6 tests passed!\n";
}

#endif //__LOGI_TESTS_ON__

} //namespace Logi
