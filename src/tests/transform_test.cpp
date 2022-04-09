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
    //TEST_xyzToRegister();
    //TEST_xyzToStack();
    //TEST_xyzFromStack();
    //TEST_xyz_bigToLittleEndian();
    
    out << '\n';

    //run tests in big-endian platform
    Transform::TEST_setPlatform(Endian::BIG);
    TEST_bytecodeToXYZ();
    TEST_xyzToBytecode();
    //TEST_xyzToRegister();
    //TEST_xyzToStack();
    //TEST_xyzFromStack();
    //TEST_xyz_bigToLittleEndian();

    //reset to system platform
    out << "\nRESETTING TO SYSTEM PLATFORM...\n";
    Transform::setPlatform();
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
    //
}

void Transform::TEST_xyzToStack()
{
    //
}

void Transform::TEST_xyzFromStack()
{
    //
}

void Transform::TEST_xyz_bigToLittleEndian()
{
    //
}

#endif //__LOGI_TESTS_ON__

} //namespace Logi
