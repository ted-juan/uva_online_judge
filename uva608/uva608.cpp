#include <string>
#include <iostream>
#include <sstream>
#include <set>
#include <bits/stdc++.h> // set_difference, set_union 

#define ONLINE_JUDGE
#ifndef ONLINE_JUDGE
#include <gmock/gmock.h>
#endif

struct coin_property
{
	char number;
	std::string weight;
};

class coins_set
{
public:
	void gather_and_calculate_input(std::istream & is);
	struct coin_property find_counterfeit();

private:
	void remove_even_coins();
	void handle_even_union();
	void handle_updown_intersection();
	std::set <char>convert_string_to_set(const std::string &);
	std::set <char>coins_difference(const std::set <char> &, const std::set <char> &);
	std::set <char>coins_intersection(const std::set <char> &, const std::set <char> &);

private:
	bool is_init_updown = false;
	std::string weight;
	std::set <char> left;
	std::set <char> right;
	std::set <char> even;
	std::set <char> up; 
	std::set <char> down;
};

std::set <char> coins_set::coins_difference(const std::set <char> &s1, const std::set <char> &s2)
{
	std::set <char> tmp;

	std::set_difference(s1.begin(), s1.end(), s2.begin(), s2.end(), std::inserter(tmp, tmp.end()));
	return tmp;
}

std::set <char> coins_set::coins_intersection(const std::set <char> &s1, const std::set <char> &s2)
{
	std::set <char> tmp;

	std::set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(), std::inserter(tmp, tmp.end()));
	return tmp;
}

void coins_set::remove_even_coins()
{
	up = coins_difference(up, even);
	down = coins_difference(down, even);
}

struct coin_property coins_set::find_counterfeit() 
{
	if (up.empty())
	{
		return {*down.begin(), "heavy"};
	}
	else if (down.empty())
	{
		return {*up.begin(), "light"};
	}
	throw;
}

std::set <char> coins_set::convert_string_to_set(const std::string &ss)
{
	std::set <char> tmp(begin(ss), end(ss));
	return tmp;
}
		
void coins_set::handle_even_union()
{
	std::set_union(left.begin(), left.end(), 
					right.begin(), right.end(), 
					std::inserter(even, even.end()));
}

void coins_set::handle_updown_intersection()
{
	std::set <char> *s1;
	std::set <char> *s2;

	if (weight == "up")
	{
		s1 = &down;
		s2 = &up;
	}
	else
	{
		s1 = &up;
		s2 = &down;
	}

	if (is_init_updown == false)
	{
		*s1 = left;
		*s2 = right;
		is_init_updown = true;
	}
	else		
	{
		*s1 = coins_intersection(*s1, left);
		*s2 = coins_intersection(*s2, right);
	}		
}						 

void coins_set::gather_and_calculate_input(std::istream & is) 
{
	for (int i=0; i<3; i++)
	{
		std::string lstring;
		std::string rstring;

		is >> lstring >> rstring >> weight;
		left = convert_string_to_set(lstring);
		right = convert_string_to_set(rstring);

		/* 1. even group union */
		/* 2. up/down group intersection */
		(weight == "even") ?  handle_even_union(): 
							  handle_updown_intersection();
	}
	/* 3. up/down group remove even element */
	remove_even_coins();
}

void print_the_result(std::ostream & os, const struct coin_property &counterfeit)
{
	os << counterfeit.number 
		<< " is the counterfeit coin and it is " 
		<< counterfeit.weight 
		<< "." << std::endl;
}

void resolve_uva(std::istream & is, std::ostream & os)
{
	std::string line;

	getline(is, line);
	int count = stoi(line);

	try
	{
		for (int i=0; i<count; i++)
		{
			coins_set coins;
			coins.gather_and_calculate_input(is);
			auto counterfeit = coins.find_counterfeit();
			print_the_result(os, counterfeit);
		}
	}
	catch (...)
	{
		os << "not found" << std::endl;
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
