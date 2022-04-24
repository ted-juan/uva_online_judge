#include <string>
#include <stack>
#include <queue>
#include <iostream>
#include <sstream>
#include <bits/stdc++.h>

#define ONLINE_JUDGE
#ifndef ONLINE_JUDGE    
#include <gmock/gmock.h>
#endif

using Stack = std::stack<int>;
using Queue = std::queue<int>;

std::string is_track_B_reasonable(Queue &track_B, Queue &track_A, int count)
{
    Stack station_S;

    while (!track_B.empty())
    {
        int tB = track_B.front();
        int tA = track_A.empty() ? 0 : track_A.front();
        int tS = station_S.empty() ? 0 : station_S.top();

        if (tB == tA)
        {
            track_A.pop();
            track_B.pop();
            continue;
        }      
        else if (tB == tS)
        {
            station_S.pop();
            track_B.pop();
            continue;
        }
        else if (track_A.empty())
        {
            return "No";
        }            
        else
        {
            track_A.pop();
            station_S.push(tA);
        }
    }
    return "Yes";
}

void read_track_B(int count, std::stringstream &seqnum, Queue &track_B)
{
    for(int i=0; i<count; i++)
    {
        int number;
        seqnum >> number;
        track_B.push(number);
    }
}

void init_track_A(int count, Queue &track_A)
{
        for (int i=1; i<=count; i++)
            track_A.push(i);
}

void resolve_uva(std::istream & is, std::ostream & os)
{
    Queue track_A;
    Queue track_B;
    std::string answer;
    std::string line;
    int count = -1;
    int first_num;
    
    while (getline(is, line))
    {
        std::stringstream seqnum(line);
        size_t n = std::count(line.begin(), line.end(), ' ');

        if (n == 0) /* no space means only one number */
        {
            seqnum >> first_num;
            if ((count == 0) & (first_num == 0)) /* the continue second count is zero */
                break;
            else    
            {
                count = first_num;
                if (count == 0) 
                    os << std::endl;

                continue;
            }                
        }

        init_track_A(count, track_A);
        read_track_B(count, seqnum, track_B);
        answer = is_track_B_reasonable(track_B, track_A, count);
        track_A = Queue();
        track_B = Queue();
        os << answer << std::endl;
    }        
}

int main(int argc, char** argv)    
{
#ifdef ONLINE_JUDGE
    resolve_uva(std::cin, std::cout);
    return 0;
#else    
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
#endif    
}