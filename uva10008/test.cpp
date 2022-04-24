#include <gmock/gmock.h>
#include <stdint.h>
#include <iostream>
#include <sstream>
#include "uva.h"

TEST(uva_test, uva_test1)
{
    std::istringstream iss(
        "1\n"\
        "A\n");
    std::ostringstream oss;

    resolve_uva(iss, oss);
    EXPECT_EQ("A 1\n", oss.str());
}

TEST(uva_test, uva_test2)
{
    std::istringstream iss(
        "1\n"\
        "AB\n");
    std::ostringstream oss;

    resolve_uva(iss, oss);
    EXPECT_EQ("A 1\n"\
              "B 1\n", oss.str());
}

TEST(uva_test, uva_test3)
{
    std::istringstream iss(
        "1\n"\
        "AaB\n");
    std::ostringstream oss;

    resolve_uva(iss, oss);
    EXPECT_EQ("A 2\n"\
              "B 1\n", oss.str());
}

TEST(uva_test, uva_test4)
{
    std::istringstream iss(
        "1\n"\
        "AABABC\n");
    std::ostringstream oss;

    resolve_uva(iss, oss);
    EXPECT_EQ("A 3\n"\
              "B 2\n"\
              "C 1\n", oss.str());
}

TEST(uva_test, uva_test5)
{
    std::istringstream iss(
        "1\n"\
        "AB\n");
    std::ostringstream oss;

    resolve_uva(iss, oss);
    EXPECT_EQ("A 1\n"\
              "B 1\n", oss.str());
}

TEST(uva_test, uva_test6)
{
    std::istringstream iss(
        "1\n"\
        "DDBDBC\n");
    std::ostringstream oss;

    resolve_uva(iss, oss);
    EXPECT_EQ("D 3\n"\
              "B 2\n"\
              "C 1\n", oss.str());
}

TEST(uva_test, uva_test7)
{
    std::istringstream iss(
        "1\n"\
        "A B\n");
    std::ostringstream oss;

    resolve_uva(iss, oss);
    EXPECT_EQ("A 1\n"\
              "B 1\n", oss.str());
}

#if 0
TEST(uva_test, uva_test7)
{
    std::istringstream iss(
        "3\n"\
        "This is a test.\n"\
        "Count me 1 2 3 4 5.\n"\
        "Wow!!!! Is this question easy?\n");
    std::ostringstream oss;

    resolve_uva(iss, oss);
    EXPECT_EQ("S 7\n"\
            "T 6\n"\
            "I 5\n"\
            "E 4\n"\
            "O 3\n"\
            "A 2\n"\
            "H 2\n"\
            "N 2\n"\
            "U 2\n"\
            "W 2\n"\
            "C 1\n"\
            "M 1\n"\
            "Q 1\n"\
            "Y 1\n"
            , oss.str());
}
#endif