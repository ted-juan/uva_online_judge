#include <gmock/gmock.h>
#include <stdint.h>
#include <iostream>
#include <sstream>
#include "uva.h"
using namespace std::string_literals;

TEST(uva_test, uva_test1)
{
    std::istringstream iss(
R"(2

7 8
********
* * * **
* *    *
* * ** *
* * *  *
*   * **
********

2 4
RRFLFF FFR
FF
RFFQ

3 4
****
*  *
****
2 2
FR  F  Q
)");    

    std::ostringstream oss;

    resolve_uva(iss, oss);
    EXPECT_EQ(
R"(5 6 W

2 3 E
)", oss.str());
}
