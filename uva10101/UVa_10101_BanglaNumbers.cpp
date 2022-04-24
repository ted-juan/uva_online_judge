#include <string>
#include <bits/stdc++.h>

//#define ONLINE_JUDGE
#ifndef ONLINE_JUDGE    
#include <gmock/gmock.h>
#endif

using namespace std;

std::string split(int64_t val) {
    string result;

    if (val >= 10000000) {
        result += split(val / 10000000);
        result += " kuti";
        val %= 10000000;
    }
    if (val >= 100000) {
        result += split(val / 100000);
        result += " lakh";
        val %= 100000;
    }
    if (val >= 1000) {
        result += split(val / 1000);
        result += " hajar";
        val %= 1000;
    }
    if (val >= 100) {
        result += split(val / 100);
        result += " shata";
        val %= 100;
    }
    if (val)
        result += " " + to_string(val);

    return result;    
}

template<typename ... Args>
std::string string_format( const std::string& format, Args ... args )
{
    int size_s = std::snprintf( nullptr, 0, format.c_str(), args ... ) + 1; // Extra space for '\0'

    if( size_s <= 0 ){ throw std::runtime_error( "Error during formatting." ); }

    auto size = static_cast<size_t>( size_s );
    auto buf = std::make_unique<char[]>( size );
    std::snprintf( buf.get(), size, format.c_str(), args ... );

    return std::string( buf.get(), buf.get() + size - 1 ); // We don't want the '\0' inside
}

std::string bangla_numbers(const std::string & numbers)
{
    std::string line;
    std::string result="";
    std::istringstream istream(numbers);
    int64_t n;
    int kase = 1;

    while (std::getline(istream, line, '\n')) {
        n = stol(line);
        result += string_format("%4d%s", kase++, ".");
        if (n)
            result += split(n);
        else
            result += " 0";

        if (!istream.eof())
            result += '\n';
    }
    return result;
}

void resolve_uva10101()
{
    int64_t val;
    int kase = 1;
    while (cin >> val) {
        cout <<setw(4)<< kase++ << ".";
        if (val)
            cout << split(val);
        else
            cout << " 0";
        cout << endl;
    }
}

int main(int argc, char** argv)    
{
#ifdef ONLINE_JUDGE
    resolve_uva10101();
    return 0;
#else    
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
#endif    
}