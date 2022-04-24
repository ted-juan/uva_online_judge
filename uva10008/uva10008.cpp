#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <map>
#include <bits/stdc++.h>

#define ONLINE_JUDGE
#ifndef ONLINE_JUDGE
#include <gmock/gmock.h>
#endif

using namespace std;

bool custom_greater (const pair<char, int> &p1, const pair<char, int> &p2)
{
	return (p1.second > p2.second) ||
		((p1.second == p2.second) && (p1.first < p2.first));
}

void traverse_string(const string &line, map <char, int> &unsorted_result)
{
	for (const char &byte : line)
	{
		if (isalpha(byte))
			unsorted_result[toupper(byte)]++;
	}
}

void read_data_to_unsorted_map(std::istream & is, map <char, int> &unsorted_result)
{
	int num;
	string line;

	getline(is, line);
	num = stoi(line);

	for (auto i=0; i<num; i++)
	{
		getline(is, line);
		traverse_string(line, unsorted_result);
	}
}

void sort_the_unsorted_map_to_sorted_vector(map <char, int> &unsorted_result, vector <pair<char, int>> &sorted_result)
{
	for (const auto &it : unsorted_result)
	{
		sorted_result.push_back(make_pair(it.first, it.second));
	}
	sort(sorted_result.begin(), sorted_result.end(), custom_greater);
}

void print_the_result(std::ostream & os , const vector <pair<char, int>> &sorted_result)
{
	for (const auto& it : sorted_result)
	{
		os << it.first << " " << it.second << endl;
	}
}

void resolve_uva(std::istream & is, std::ostream & os)
{
	vector <pair<char, int>> sorted_result;
	map <char, int> unsorted_result;

	read_data_to_unsorted_map(is, unsorted_result);
	sort_the_unsorted_map_to_sorted_vector(unsorted_result, sorted_result);
	print_the_result(os, sorted_result);
}

int main(int argc, char** argv)
{
#ifdef ONLINE_JUDGE
	resolve_uva(cin, cout);
	return 0;
#else
	testing::InitGoogleMock(&argc, argv);
	return RUN_ALL_TESTS();
#endif
}
