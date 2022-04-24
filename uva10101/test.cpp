#include <gmock/gmock.h>
#include <stdint.h>
#include "BanglaNumbers.h"

TEST(BanglaNumbers, negative)
{
    EXPECT_EQ("   1. -1", bangla_numbers("-1"));
}

TEST(BanglaNumbers, 0)
{
    EXPECT_EQ("   1. 0", bangla_numbers("0"));
}

TEST(BanglaNumbers, 1)
{
    EXPECT_EQ("   1. 1", bangla_numbers("1"));
}

TEST(BanglaNumbers, 12)
{
    EXPECT_EQ("   1. 12", bangla_numbers("12"));
}

TEST(BanglaNumbers, 123)
{
    EXPECT_EQ("   1. 1 shata 23", bangla_numbers("123"));
}

TEST(BanglaNumbers, 1234)
{
    EXPECT_EQ("   1. 1 hajar 2 shata 34", bangla_numbers("1234"));
}

TEST(BanglaNumbers, 12345)
{
    EXPECT_EQ("   1. 12 hajar 3 shata 45", bangla_numbers("12345"));
}

TEST(BanglaNumbers, 123456)
{
    EXPECT_EQ("   1. 1 lakh 23 hajar 4 shata 56", bangla_numbers("123456"));
}

TEST(BanglaNumbers, 1234567)
{
    EXPECT_EQ("   1. 12 lakh 34 hajar 5 shata 67", bangla_numbers("1234567"));
}

TEST(BanglaNumbers, 12345678)
{
    EXPECT_EQ("   1. 1 kuti 23 lakh 45 hajar 6 shata 78", bangla_numbers("12345678"));
}

TEST(BanglaNumbers, 123456789)
{
    EXPECT_EQ("   1. 12 kuti 34 lakh 56 hajar 7 shata 89", bangla_numbers("123456789"));
}

TEST(BanglaNumbers, 1234567890)
{
    EXPECT_EQ("   1. 1 shata 23 kuti 45 lakh 67 hajar 8 shata 90", bangla_numbers("1234567890"));
}

TEST(BanglaNumbers, 12345678901)
{
    EXPECT_EQ("   1. 1 hajar 2 shata 34 kuti 56 lakh 78 hajar 9 shata 1", bangla_numbers("12345678901"));
}

TEST(BanglaNumbers, 123456789012)
{
    EXPECT_EQ("   1. 12 hajar 3 shata 45 kuti 67 lakh 89 hajar 12", bangla_numbers("123456789012"));
}

TEST(BanglaNumbers, 1234567890123)
{
    EXPECT_EQ("   1. 1 lakh 23 hajar 4 shata 56 kuti 78 lakh 90 hajar 1 shata 23", bangla_numbers("1234567890123"));
}

TEST(BanglaNumbers, 12345678901234)
{
    EXPECT_EQ("   1. 12 lakh 34 hajar 5 shata 67 kuti 89 lakh 1 hajar 2 shata 34", bangla_numbers("12345678901234"));
}

TEST(BanglaNumbers, 123456789012345)
{
    EXPECT_EQ("   1. 1 kuti 23 lakh 45 hajar 6 shata 78 kuti 90 lakh 12 hajar 3 shata 45", bangla_numbers("123456789012345"));
}

TEST(BanglaNumbers, 123456789012000)
{
    EXPECT_EQ("   1. 1 kuti 23 lakh 45 hajar 6 shata 78 kuti 90 lakh 12 hajar", bangla_numbers("123456789012000"));
}

TEST(BanglaNumbers, 123456000000000)
{
    EXPECT_EQ("   1. 1 kuti 23 lakh 45 hajar 6 shata kuti", bangla_numbers("123456000000000"));
}

TEST(BanglaNumbers, 100000000000000)
{
    EXPECT_EQ("   1. 1 kuti kuti", bangla_numbers("100000000000000"));
}

TEST(BanglaNumbers, example)
{
    EXPECT_EQ("   1. 23 hajar 7 shata 64\n"
              "   2. 45 lakh 89 hajar 7 shata 45 kuti 89 lakh 73 hajar 9 shata 58",
              bangla_numbers("23764\n45897458973958"));
}