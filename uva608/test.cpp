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
ABCD EFGH even
ABCI EFJK up
ABIJ EFGH even
ABC DEF up
GHI JKL even
EF DA up        
)");    

    std::ostringstream oss;

    resolve_uva(iss, oss);
    EXPECT_EQ(
R"(K is the counterfeit coin and it is light.
D is the counterfeit coin and it is light.
)", oss.str());
}

TEST(uva_test, uva_test2)
{
    std::istringstream iss(
R"(15
ABC DEF up 
GHI JKL even 
EF DA up 
AFG JKL down 
A J down 
A D even 
ED FG even 
AB CI up 
A D up 
IL JK even 
A B even 
E L down 
BEF JIL down 
J A even 
CEF BJI even 
AC BD down
AC EF down
A F even
IJK ABC even
C L even
L F up
IJK ABC even
C L even
L F down
ABCDE FGHIJ even
EIL ADJ down
K J even
CBA DEF up
AF BC up
BA CD up
CBA DEF up
A B up
BA CD up
CBA DEF up
B A down
BA CD up
CBA DEF down
AF BC down
BA CD down
CBA DEF down
A B down
BA CD down
CBA DEF down
B A up
BA CD down
)");    

    std::ostringstream oss;

    resolve_uva(iss, oss);
    EXPECT_EQ(
R"(D is the counterfeit coin and it is light.
J is the counterfeit coin and it is heavy.
A is the counterfeit coin and it is heavy.
E is the counterfeit coin and it is light.
L is the counterfeit coin and it is heavy.
C is the counterfeit coin and it is light.
F is the counterfeit coin and it is light.
F is the counterfeit coin and it is heavy.
L is the counterfeit coin and it is light.
A is the counterfeit coin and it is heavy.
A is the counterfeit coin and it is heavy.
A is the counterfeit coin and it is heavy.
A is the counterfeit coin and it is light.
A is the counterfeit coin and it is light.
A is the counterfeit coin and it is light.
)", oss.str());
}
