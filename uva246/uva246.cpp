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
	poker_game(std::istream & is, int first_card)
	{
		init_deck(is, first_card);
	};	

	void deal_cards_to_each_pile();
	void deal_one_card();
	void pick_10_20_30();
	void record_pile_state();
	bool is_game_over(std::ostream & os);
private:
	void init_deck(std::istream & is, int first_card);
	bool is_deck_empty();
	bool is_pile_empty();
	bool is_draw_condition();
	void pick_front_card(std::deque<int> &current_pile, int card)
	{
		deck_.push_back(card);
		current_pile.pop_front(); 
	}
	void pick_back_card(std::deque<int> &current_pile, int card)
	{
		deck_.push_back(card);
		current_pile.pop_back(); 
	}
	void dealt_from_the_deck(int pile_index)
	{
		piles_[pile_index].push_back(deck_.front());
		deck_.pop_front();
	}			
	void increase_pile_index()
	{
		current_pile_index_ = (current_pile_index_ + 1) % max_piles_;
	}
	int get_current_pile_index_()
	{
		return current_pile_index_;	
	}
private:
	const int max_piles_ = 7;
	int number_of_dealt_card_ = 0;
	int current_pile_index_ = 0;
	pile_deques piles_;
	std::deque<int> deck_;
	std::set<pile_deques> snapshot_record_;
};

void poker_game::init_deck(std::istream & is, int first_card)
{
	int card;

	deck_.push_back(first_card);
	for (int i=0; i<51; i++)
	{
		is >> card;
		deck_.push_back(card);
	}
}	

void poker_game::deal_cards_to_each_pile()
{
	for (int i=0; i<max_piles_; i++)
	{
		std::deque<int> new_pile;
		new_pile.push_back(deck_.front());
		deck_.pop_front();
		piles_.push_back(new_pile);
	}

	for (int i=0; i<max_piles_; i++)
		dealt_from_the_deck(i);

	number_of_dealt_card_ = max_piles_*2;
	record_pile_state();
}

void poker_game::deal_one_card()
{
	for (int i=0; i<max_piles_; i++)
	{
		int index = get_current_pile_index_();
		if (!(piles_[index].empty()))
		{
			dealt_from_the_deck(index);
			number_of_dealt_card_++;
			break;
		}			
		increase_pile_index();
	}
}

void poker_game::pick_10_20_30()
{
	int index = get_current_pile_index_();
	std::deque<int> &pile = piles_[index];

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
	pile_deques piles_state = piles_;
	piles_state.push_back(deck_);
	snapshot_record_.insert(piles_state);
}

bool poker_game::is_draw_condition()
{
	pile_deques piles_state = piles_;
	piles_state.push_back(deck_);

	if (snapshot_record_.find(piles_state) != snapshot_record_.end())
		return true;

	return false;
}

bool poker_game::is_deck_empty()
{
	return deck_.empty();
}

bool poker_game::is_pile_empty()
{
	for (int i=0; i<max_piles_; i++)
	{
		if (!(piles_[i].empty()))
			return false;
	}		
	return true;
}

bool poker_game::is_game_over(std::ostream & os)
{
	if (is_draw_condition() == true)
		os << "Draw: " << number_of_dealt_card_ << std::endl;
	else if (is_deck_empty() == true)
		os << "Loss: " << number_of_dealt_card_ << std::endl;
	else if (is_pile_empty() == true)		
		os << "Win : " << number_of_dealt_card_ << std::endl;
	else	
		return false;

	return true;
}

void resolve_uva(std::istream & is, std::ostream & os)
{
	while (1)
	{
		int first_card;

		is >> first_card;
		if (first_card == 0)
			break;

		poker_game poker(is, first_card);
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
