#include "test/TestCommon.h"
#include <iostream>
using namespace std;

int main (int argc, char** argv)
{

    InitGoogleTest(&argc, argv);

    const auto returnValue =  RUN_ALL_TESTS();

    return returnValue;

    return 0;
}