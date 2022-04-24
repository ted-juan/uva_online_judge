#include <string>
#include <vector>
#include <bits/stdc++.h>
#include <algorithm> 

#define ONLINE_JUDGE
#ifndef ONLINE_JUDGE    
#include <gmock/gmock.h>
#endif

using namespace std;

std::string list_first_line(const std::string & numbers)
{
    string result = "Original number was " + numbers + "\n";
    return result;              
}

int64_t ascending_number(const std::string & numbers)
{
    string seqnum = numbers;
    std::sort(seqnum.begin(), seqnum.end());
    return stol(seqnum);              
}

int64_t descending_number(const std::string & numbers)
{
    string seqnum = numbers;
    std::sort(seqnum.begin(), seqnum.end(), greater<int64_t>());
    return stol(seqnum);              
}

std::string list_equation(const int64_t num1, const int64_t num2, int64_t answer)
{
    return to_string(num1) + " - " + to_string(num2) + " = " + to_string(answer) + '\n';
}

std::string calculate_chain_len(const std::string & numbers)
{
    int64_t chain_num = 0;
    std::string result="";
    std::vector<int64_t> records;
    int64_t answer = stoi(numbers);

    do 
    {
        if (chain_num > 0)
            records.push_back(answer);

        int64_t descend_num = descending_number(to_string(answer));
        int64_t ascend_num = ascending_number(to_string(answer));
        answer = descend_num - ascend_num;
        result += list_equation(descend_num, ascend_num, answer);
        chain_num++;
    } while(find(records.begin(), records.end(), answer)== records.end());

    result += "Chain length " + to_string(chain_num); 
    return result;
}

std::string resolve_uva263(const std::string & line)
{
    string number;
    string result="";
    istringstream istream(line);

    while (std::getline(istream, number)) {
        if (stol(number)==0)
            break;

        result += list_first_line(number);
        result += calculate_chain_len(number);
        result += "\n\n";
    }
    return result;
}

void resolve_uva263()
{
    string result="";
    string input_data;
    string line;
    
    while (getline(cin, line) && !cin.eof())
    {
        input_data += line;
        input_data += "\n";
    }    
    result = resolve_uva263(input_data);
    cout << result;
}

int main(int argc, char** argv)    
{
#ifdef ONLINE_JUDGE
    resolve_uva263();
    return 0;
#else    
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
#endif    
}