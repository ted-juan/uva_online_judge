#include <gmock/gmock.h>
#include <stdint.h>
#include <iostream>
#include <sstream>
#include "uva.h"
using namespace std::string_literals;

TEST(uva_test, uva_test1)
{
    std::istringstream iss (
        "5\n"\
        "1 2 3 4 5\n"\
        "5 4 1 2 3\n"\
        "0\n"\
        "7\n"\
        "4 5 3 7 6 2 1\n"\
        "0\n"\
        "0\n"
    );
    std::ostringstream oss;

    resolve_uva(iss, oss);
    EXPECT_EQ(
        "Yes\n"
        "No\n"
        "\n"
        "Yes\n"
        "\n"
        , oss.str());
}

TEST(uva_test, uva_test2)
{
    std::istringstream iss (
        "5\n"\
        "1 2 3 4 5\n"\
        "5 4 1 2 3\n"\
        "1 4 3 2 5\n"\
        "3 4 2 5 1\n"\
        "3 4 2 1 5\n"\
        "4 3 5 2 1\n"\
        "0\n"\
    );
    std::ostringstream oss;

    resolve_uva(iss, oss);
    EXPECT_EQ(
        "Yes\n"
        "No\n"
        "Yes\n"
        "Yes\n"
        "Yes\n"
        "Yes\n"
        "\n"
        , oss.str());
}