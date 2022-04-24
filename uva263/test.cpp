#include <gmock/gmock.h>
#include <stdint.h>
#include "uva263.h"

TEST(uva_test, first_line)
{
    EXPECT_EQ("Original number was 123456789\n", list_first_line("123456789"));
}

TEST(uva_test, ascending_number)
{
    EXPECT_EQ(123456789, ascending_number("987653421"));
}

TEST(uva_test, descending_number)
{
    EXPECT_EQ(987654321, descending_number("123457896"));
}


TEST(uva_test, list_equation)
{
    EXPECT_EQ("987654321 - 123456789 = 864197532\n", 
              list_equation(987654321, 123456789, 864197532));
}

TEST(uva_test, calculate_chain1)
{
    EXPECT_EQ("987654321 - 123456789 = 864197532\n"
              "987654321 - 123456789 = 864197532\n"
              "Chain length 2"
              , calculate_chain_len("123456789"));
}

TEST(uva_test, calculate_chain2)
{
    EXPECT_EQ("4321 - 1234 = 3087\n"
              "8730 - 378 = 8352\n"
              "8532 - 2358 = 6174\n"
              "7641 - 1467 = 6174\n"
              "Chain length 4"
              , calculate_chain_len("1234"));
}

TEST(uva_test, complet_test1)
{
    EXPECT_EQ("Original number was 444\n"
              "444 - 444 = 0\n"
              "0 - 0 = 0\n"
              "Chain length 2\n\n"
              , resolve_uva263("444"));
}

TEST(uva_test, complet_test3)
{
    EXPECT_EQ("", resolve_uva263("0"));
}

TEST(uva_test, complet_test4)
{
    EXPECT_EQ("Original number was 1\n"
              "1 - 1 = 0\n"
              "0 - 0 = 0\n"
              "Chain length 2\n\n"
              , resolve_uva263("1\n0"));
}