#ifndef __LOGI_TESTING_H__
#define __LOGI_TESTING_H__

//Logi includes
#include "Transform.h"
#include "Stream.h"

namespace Logi
{

#ifdef __LOGI_TESTS_ON__

void run_all_tests()
{
    std::ostream& out = Stream::getInstance()->get();
    out << "RUNNING TESTS:\n";

    //transform
    out << "TRANSFORM TESTS:\n";
    Transform::TEST_run_all_tests();

    //
}

#endif //__LOGI_TESTS_ON__

} //namespace Logi

#endif //__LOGI_TESTING_H__
