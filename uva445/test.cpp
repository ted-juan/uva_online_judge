#include <gmock/gmock.h>
#include <stdint.h>
#include "uva445.h"

TEST(uva_test, resolve_uva445_13)
{
    EXPECT_EQ("T\n\n\n\n\n\nT\n", resolve_uva445("1T!!!\n!\n1T"));
}

TEST(uva_test, resolve_uva445_12)
{
    EXPECT_EQ("T\n\nT\n", resolve_uva445("1T\n\n1T"));
}

TEST(uva_test, resolve_uva445_8)
{
    EXPECT_EQ("XX   X\n"\
              "XXXX X\n", 
                resolve_uva445("11X21b1X\n4X1b1X"));
}

TEST(uva_test, resolve_uva445_11)
{
    EXPECT_EQ("AABBB\n"\
              "CCCCCTTTTTT\n"\
              "XXXXXXTTTTTTTTTT\n\n"\
              , resolve_uva445("2A3B!5C6T\n15X19T!"));
}

TEST(uva_test, resolve_uva445_10)
{
    EXPECT_EQ("AABBB\n"\
              "CCCCCTTTTTT\n"\
              "XXXXXXTTTTTTTTTT\n\n"\
              "AAAAA\n"\
              "BBBBB\n"\
              "CCCCC\n"\
              "DDDDD\n"\
              "EEEEE\n\n"
              , resolve_uva445("2A3B!5C6T\n15X19T!\n5A!5B!5C!5D!5E!"));
}

TEST(uva_test, resolve_uva445_9)
{
    EXPECT_EQ("T TTTTT\n"\
              "T  T TT\n"\
              "T T  TT\n"\
              "T   T T\n"\
              "TTT   T\n"\
              "T   T T\n"\
              "TTTTT*T\n"
              , resolve_uva445("1T1b5T!1T2b1T1b2T!1T1b1T2b2T!1T3b1T1b1T!3T3b1T!1T3b1T1b1T!5T1*1T"));
}

TEST(uva_test, resolve_uva445_1)
{
    EXPECT_EQ("T\n", resolve_uva445("1T"));
}

TEST(uva_test, resolve_uva445_2)
{
    EXPECT_EQ("TXX\n", resolve_uva445("1T2X"));
}

TEST(uva_test, resolve_uva445_3)
{
    EXPECT_EQ("TXXYYY\n", resolve_uva445("1T2X3Y"));
}

TEST(uva_test, resolve_uva445_4)
{
    EXPECT_EQ(" T  X\n", resolve_uva445("1b1T2b1X"));
}

TEST(uva_test, resolve_uva445_5)
{
    EXPECT_EQ("T\n\n", resolve_uva445("1T!"));
}

TEST(uva_test, resolve_uva445_6)
{
    EXPECT_EQ("TT\n\n", resolve_uva445("11T!"));
}

TEST(uva_test, resolve_uva445_7)
{
    EXPECT_EQ("XX   X\n", resolve_uva445("11X21b1X"));
}