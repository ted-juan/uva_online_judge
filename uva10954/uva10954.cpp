#include <string>
#include <queue>
#include <iostream>
#include <sstream>
#include <bits/stdc++.h>

#define ONLINE_JUDGE
#ifndef ONLINE_JUDGE    
#include <gmock/gmock.h>
#endif

using priority_queue_gt = std::priority_queue<int, std::vector<int>, std::greater<int> >;

int compute_cost(priority_queue_gt &seq_queue)
{
    int total_cost = 0;

    while (seq_queue.size() >= 2)
    {
        int n1 = seq_queue.top();
        seq_queue.pop();
        int n2 = seq_queue.top();
        seq_queue.pop();
        int cost = n1 + n2;
        seq_queue.push(cost);
        total_cost += cost;
    }
    return total_cost;
}

void read_sequence_number(std::istream & is, int count, priority_queue_gt &seq_queue)
{
    for(int i=0; i<count; i++)
    {
        int number;
        is >> number;
        seq_queue.push(number);
    }
    is.ignore(1, '\n');
}

void resolve_uva(std::istream & is, std::ostream & os)
{
    int count;
    
    while (is >> count)
    {
        if (count == 0)
            break;

        priority_queue_gt seq_queue = priority_queue_gt();
        read_sequence_number(is, count, seq_queue);
        os << compute_cost(seq_queue) << std::endl;
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