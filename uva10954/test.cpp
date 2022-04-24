#include <gmock/gmock.h>
#include <stdint.h>
#include <iostream>
#include <sstream>
#include "uva.h"
using namespace std::string_literals;

TEST(uva_test, uva_test1)
{
    std::istringstream iss (
        "3\n"\
        "1 2 3\n"\
        "4\n"\
        "4 1 2 3\n"\
        "0\n"
    );
    std::ostringstream oss;

    resolve_uva(iss, oss);
    EXPECT_EQ(
        "9\n"
        "19\n"
        , oss.str());
}

TEST(uva_test, uva_test2)
{
    std::istringstream iss (
        "17\n"\
        "7 6 60 70 78 44 86 21 7 11 33 44 93 87 68 72 92 \n"\
        "2\n"\
        "56 91\n"\
        "0"
    );
    std::ostringstream oss;

    resolve_uva(iss, oss);
    EXPECT_EQ(
        "3349\n"
        "147\n"
        , oss.str());
}

TEST(uva_test, uva_test3)
{
    std::istringstream iss (
        "3\n"\
        "6 5 4\n"\
        "10\n"\
        "9 5 48 2 4 5 6 3 5 4\n"\
        "10\n"\
        "3 4 5 4 7 2 3 8 4 5\n"\
        "0\n"
    );
    std::ostringstream oss;

    resolve_uva(iss, oss);
    EXPECT_EQ(
        "24\n"
        "224\n"
        "147\n"
        , oss.str());
}
