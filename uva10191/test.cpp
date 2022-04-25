#include <gmock/gmock.h>
#include <stdint.h>
#include <iostream>
#include <sstream>
#include "uva.h"
using namespace std::string_literals;

TEST(uva_test, uva_test1)
{
    std::istringstream iss (
        "4\n"\
        "10:00 12:00 Lectures\n"\
        "12:00 13:00 Lunch, like always\n"\
        "13:00 15:00 Boring lectures..\n"\
        "15:30 17:45 Readin\n"
        "4\n"\
        "10:00 12:00 Lectures\n"\
        "12:00 13:00 Lunch, just lunch.\n"\
        "13:00 15:00 Lectures, lectures... oh, no!\n"\
        "16:45 17:45 Reading (to be or not to be?)\n"\
        "4\n"\
        "10:00 12:00 Lectures, as everyday.\n"\
        "12:00 13:00 Lunch, again!!!\n"\
        "13:00 15:00 Lectures, more lectures!\n"\
        "15:30 17:15 Reading (I love reading, but should I schedule it?)\n"\
        "1\n"\
        "12:00 13:00 I love lunch! Have you ever noticed it? :)\n"
    );
    std::ostringstream oss;

    resolve_uva(iss, oss);
    EXPECT_EQ(
        "Day #1: the longest nap starts at 15:00 and will last for 30 minutes.\n"\
        "Day #2: the longest nap starts at 15:00 and will last for 1 hours and 45 minutes.\n"\
        "Day #3: the longest nap starts at 17:15 and will last for 45 minutes.\n"\
        "Day #4: the longest nap starts at 13:00 and will last for 5 hours and 0 minutes.\n"
        , oss.str());
}
