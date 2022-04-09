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

void Transform::TEST_run_all_tests()
{
    out << "RUNNING TRANSFORM TESTS...\n";
    out << "PLATFORM IS ";
    PLATFORM == Endian::LITTLE ? out << "LITTLE" : out << "BIG";
    out << "-ENDIAN\n";

    TEST_bytecodeToXYZ();
    //TEST_xyzToBytecode();
    //TEST_xyzToRegister();
    //TEST_xyzToStack();
    //TEST_xyzFromStack();
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

    //{0x12,0xAB,0x34,0xCD,0x56,0xEF,0x78,0xCA};

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

    out << "TEST_bytecodeToXYZ() passed!\n";
}

void Transform::TEST_xyzToBytecode()
{
    //U1 bytes[8] = {0x12,0xAB,0x34,0xCD,0x56,0xEF,0x78,0xCA};
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
