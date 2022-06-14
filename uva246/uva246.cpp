#include <string>
#include <iostream>
#include <sstream>
#include <deque>
#include <queue>
#include <vector>
#include <set>

#define ONLINE_JUDGE
#ifndef ONLINE_JUDGE
#include <gmock/gmock.h>
#endif

using pile_deques = std::vector<std::deque<int>>; 

class poker_game
{
public:
	poker_game(std::istream & is, int first)
	{
		init_deck(is, first);
    };	

	void deal_cards_to_each_pile();
	void deal_one_card();
	void pick_10_20_30();
	void record_pile_state();
	bool is_game_over(std::ostream & os);
private:
	void init_deck(std::istream & is, int first);
	bool is_deck_empty();
	bool is_pile_empty();
	bool is_draw_condition();
	void pick_front_card(std::deque<int> &pile, int card)
	{
		deck.push_back(card);
		pile.pop_front(); 
	}
	void pick_back_card(std::deque<int> &pile, int card)
	{
		deck.push_back(card);
		pile.pop_back(); 
	}
	void dealt_from_the_deck(int pile_index)
	{
		piles[pile_index].push_back(deck.front());
		deck.pop_front();
	}			
	void increase_pile_index()
	{
		current_pile_index = (current_pile_index + 1) % max_piles;
	}
	int get_current_pile_index()
	{
		return current_pile_index;	
	}
private:
	const int max_piles = 7;
	int number_of_dealt_card = 0;
	int current_pile_index = 0;
	std::deque<int> current_pile;
	pile_deques piles;
	std::deque<int> deck;
	std::set<pile_deques> snapshot_record;
};

void poker_game::init_deck(std::istream & is, int first)
{
	int number;

	deck.push_back(first);
	for (int i=0; i<51; i++)
	{
		is >> number;
		deck.push_back(number);
	}
}	

void poker_game::deal_cards_to_each_pile()
{
	for (int i=0; i<max_piles; i++)
	{
		std::deque<int> new_pile;
		new_pile.push_back(deck.front());
		deck.pop_front();
		piles.push_back(new_pile);
	}

	for (int i=0; i<max_piles; i++)
		dealt_from_the_deck(i);

	number_of_dealt_card = max_piles*2;
	record_pile_state();
}

void poker_game::deal_one_card()
{
	for (int i=0; i<max_piles; i++)
	{
		int index = get_current_pile_index();
		if (!(piles[index].empty()))
		{
			dealt_from_the_deck(index);
			number_of_dealt_card++;
			break;
		}			
		increase_pile_index();
	}
}

void poker_game::pick_10_20_30()
{
	int index = get_current_pile_index();
	std::deque<int> &pile = piles[index];

	while(1)
	{
		int size = pile.size();
		if (size < 3)
			break;

		int first = pile[0];
		int second = pile[1];
		int last = pile[size - 1];
		int second_to_last = pile[size - 2];
		/* if size == 3. third_to_last is equal first */
		int third_to_last = pile[size - 3];

		if ((first + second + last) % 10 == 0)
		{
			pick_front_card(pile, first);
			pick_front_card(pile, second);
			pick_back_card(pile, last);
		}			
		else if ((first + second_to_last + last) % 10 == 0)
		{
			pick_front_card(pile, first);
			pick_back_card(pile, second_to_last);
			pick_back_card(pile, last);
		}
		else if ((third_to_last + second_to_last + last) % 10 == 0)
		{
			pick_back_card(pile, third_to_last);
			pick_back_card(pile, second_to_last);
			pick_back_card(pile, last);
		}
		else
		{
			break;
		}
	}		
	increase_pile_index();
}

void poker_game::record_pile_state()
{
	pile_deques piles_state = piles;
	piles_state.push_back(deck);
	snapshot_record.insert(piles_state);
}

bool poker_game::is_draw_condition()
{
	pile_deques piles_state = piles;
	piles_state.push_back(deck);

	if (snapshot_record.find(piles_state) != snapshot_record.end())
		return true;

	return false;
}

bool poker_game::is_deck_empty()
{
	return deck.empty();
}

bool poker_game::is_pile_empty()
{
	for (int i=0; i<max_piles; i++)
	{
		if (!(piles[i].empty()))
			return false;
	}		
	return true;
}

bool poker_game::is_game_over(std::ostream & os)
{
	if (is_draw_condition() == true)
		os << "Draw: " << number_of_dealt_card << std::endl;
	else if (is_deck_empty() == true)
		os << "Loss: " << number_of_dealt_card << std::endl;
	else if (is_pile_empty() == true)		
		os << "Win : " << number_of_dealt_card << std::endl;
	else	
		return false;

	return true;
}

void resolve_uva(std::istream & is, std::ostream & os)
{
	std::string line;
	int num;
	std::stringstream seqnum;

	while (1)
	{
		is >> num;
		if (num == 0)
			break;

		poker_game poker(is, num);
		poker.deal_cards_to_each_pile();

		while (1)
		{
			poker.deal_one_card();
			poker.pick_10_20_30();

			if (poker.is_game_over(os)==true)
				break;

			poker.record_pile_state();
		}
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
