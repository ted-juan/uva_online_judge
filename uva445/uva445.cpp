#include <string>
#include <vector>
#include <bits/stdc++.h>

#define ONLINE_JUDGE
#ifndef ONLINE_JUDGE    
#include <gmock/gmock.h>
#endif

using namespace std;

char transform_character(char character)
{
    map<char, char> specific_symbol = {{'b', ' '}, {'!', '\n'}};
    std::map<char, char>::iterator it = specific_symbol.find(character);

    if (it != specific_symbol.end())
        return specific_symbol.find(character)->second;
    else    
        return character;
}

std::string output_symbol(const int num, const char character)
{
    string result="";

    for (auto i=0; i<num; i++)
        result += character;

    return result;    
}

std::string draw_maze(const std::string & input_data)
{
    char byte;
    char symbol;
    string result;
    string tmp;
    string line;
    std::istringstream istream(input_data);

    while (getline(istream, line, '\n'))
    {
        int num = 0;
        std::istringstream ssdata(line);
        while (ssdata >> byte)
        {   
            symbol = transform_character(byte) ;
            if (symbol>='0' && symbol <= '9')
            {
                num += symbol - '0';
                continue;
            }
            else if (symbol == '\n')
            {
                result += "\n";
                continue;
            }
            result += output_symbol(num, symbol);
            num = 0;
        }        
        result += "\n";
    }        
    return result;
}

std::string resolve_uva445(const std::string &input_data)
{
    string result;
    result = draw_maze(input_data);
    return result;
}

void resolve_uva445()
{
    string input_data;
    string line;
    char byte;
    
    while (cin.get(byte) && !cin.eof())
    {
       input_data += byte;
    }    
    cout << draw_maze(input_data); 
}

int main(int argc, char** argv)    
{
#ifdef ONLINE_JUDGE
    resolve_uva445();
    return 0;
#else    
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
#endif    
}