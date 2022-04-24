#include <string>
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <iomanip>

//#define ONLINE_JUDGE
#ifndef ONLINE_JUDGE    
#include <gmock/gmock.h>
#endif

class Poker
{
public:
    Poker(){};
    Poker(char val, char suit):value_(val), suit_(suit) {};

    friend bool operator<(Poker &it1, Poker &it2)
    {
        return it1.value_ < it2.value_;
    }
    friend std::istream &operator>> (std::istream & is, Poker &card)
    {
        is >> std::setw(1) >> card.value_;
        is >> std::setw(1) >> card.suit_;
        return is;
    }
    friend std::ostream &operator<< (std::ostream & os, const Poker &card)
    {
        os << card.value_ << card.suit_;
        return os;
    }
public:
    char value_;
    char suit_;
};

using Poker_cards = std::vector<Poker>;

struct poker_table_t
{
    std::string result;
    uint32_t priority;
};

std::map<std::string, struct poker_table_t> poker_table
{
    /* key     result     priority*/
    /* key = {most_num, second_num, is_continuos, is_same_suit} */
    {"11YY", {"straight-flush", 0}},
	{"41NN", {"four-of-a-kind", 1}},   
	{"32NN", {"full-house"    , 2}},   
	{"11NY", {"flush"         , 3}},   
	{"11YN", {"straight"      , 4}},   
	{"31NN", {"three-of-a-kind",5}},
	{"22NN", {"two-pairs"     , 6}},
	{"21NN", {"one-pair"      , 7}},
	{"11NN", {"highest-card"  , 8}}
};

void transfer_face_value_to_number(Poker_cards &cards)
{
   std::map<char, char> face_value_table = 
       {{'A', 14}, {'T', 10}, {'J', 11}, {'Q', 12}, {'K', 13}};
   
   for (auto &it : cards)
   {
       if (face_value_table.count(it.value_))
            it.value_ = face_value_table[it.value_];
       else            
            it.value_ -= '0';
   }
}

std::string is_the_continous_num(const Poker_cards &compose)
{
    Poker_cards cards(compose);

    transfer_face_value_to_number(cards);
    std::sort(cards.begin(), cards.end(), 
             [] (auto & lt, auto & rt) 
    {
        return (lt.value_ < rt.value_); 
    });

    auto it = cards.begin();
    size_t count = 0;
    size_t len = compose.size()-1;

    for(size_t i=0; i<len; i++)
    {
        /* ex: 2,3,4,5,6 or 2,3,4,5,14(A) */
        if (((it[i].value_ + 1) == it[i+1].value_) || 
            (it[i].value_ + 9 == 14)) 
        {
            count++;
            continue;
        }            
        else
            count=0;
    }
    return (count >= len) ? "Y" : "N";
}

std::string the_first_two_max_same_num(const Poker_cards &cards)
{
    std::map<char, int> occurrences_map;
    std::vector <std::pair<char, int>> occurrences;
    for (const auto &it : cards)
	{
		occurrences_map[it.value_]++;
	}
    std::copy(occurrences_map.begin(), occurrences_map.end(),
            std::back_inserter<std::vector<std::pair<char, int>>>(occurrences));

	std::sort(occurrences.begin(), occurrences.end(), 
             [] (auto & lt, auto & rt) 
    {
        return (lt.second > rt.second); 
    });
    std::string s = std::to_string(occurrences[0].second) +
                    std::to_string(occurrences[1].second);
    return s;
}    
   
std::string is_the_same_suit(const Poker_cards &cards)
{
    int len = cards.size();
    std::map<char, int> occurrences_map;
    std::vector <std::pair<char, int>> occurrences;
    for (const auto &it : cards)
	{
		occurrences_map[it.suit_]++;
	}
    std::copy(occurrences_map.begin(), occurrences_map.end(),
            std::back_inserter<std::vector<std::pair<char, int>>>(occurrences));

    /* if yes, means only one kine of suit */
    return (occurrences[0].second == len) ? "Y" : "N";
}

std::string compose_the_best_cards(Poker_cards hand, Poker_cards deck)
{   
    size_t len = deck.size();
    Poker_cards compose{len};
    uint32_t the_highest_priority = 8;
    std::string the_best_combination = "11NN";

    for (size_t i=0 ;i<=len; i++)
    {
        auto last = std::copy(deck.begin(), deck.begin()+i, compose.begin());
        std::sort(hand.begin(), hand.end());
        do
        {
            std::copy(hand.begin(), hand.begin()+(5-i), last);
            std::string key = the_first_two_max_same_num(compose) +
                            is_the_continous_num(compose) +
                            is_the_same_suit(compose);

            if (poker_table[key].priority < the_highest_priority)
            {
                the_highest_priority = poker_table[key].priority;
                the_best_combination = key;
            }                
        } while ((i> 0) && next_permutation(hand.begin(), hand.end()));
    }
    return poker_table[the_best_combination].result;
}

Poker_cards get_cards(std::stringstream &ss)
{
    std::vector<Poker> cards;

    for(int i=0; i<5; i++)
    {
        Poker card;
        ss >> card;
        cards.push_back(card);
    }
    return cards;
}

void print_the_result(std::ostream & os, const Poker_cards &hand, 
                      const  Poker_cards &deck, const std::string best_result)
{
    os << "Hand: ";
    for (auto &it : hand)
        os << it << " ";

    os << "Deck: ";
    for (auto &it : deck)
        os << it << " ";

    os << "Best hand: " << best_result << std::endl;
}

void resolve_uva(std::istream & is, std::ostream & os)
{
    std::string line;
    
    while (getline(is, line))
    {
        std::stringstream ss(line);
        auto hand = get_cards(ss);
        auto deck = get_cards(ss);
        auto best_result= compose_the_best_cards(hand, deck);
        print_the_result(os, hand, deck, best_result);
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