#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <functional>

#define ONLINE_JUDGE
#ifndef ONLINE_JUDGE
#include <gmock/gmock.h>
#endif

enum class direction_t
{
	east,
	south,
	west,
	north
};

struct position_t
{
    position_t()
        : x(0)
        , y(0)
		, dir(direction_t::north)
    {}
	int x;
	int y;
	direction_t dir;
};

struct move_position_t
{
	int move_x;
	int move_y;
};

class Maze_Traversal
{
public:
	Maze_Traversal(std::istream & is)
	{
		init_maze(is);
    };	
	position_t get_position();
	bool cmd_handle(char cmd);
	typedef void (Maze_Traversal::*cmd_func)(void);

private:
	void init_maze(std::istream & is);
	void move_forward();
	void turn_right();
	void turn_left();
	std::vector<std::string> maze;
	std::map<char, cmd_func> cmd_func_map;
	position_t current_pos_;
};

void Maze_Traversal::init_maze(std::istream & is)
{
	int row_len;
	int column_len;

	is >> row_len >> column_len;
	is.ignore();

	for (int i=0; i<row_len; i++)
	{
		std::string line;

		std::getline(is, line);
		maze.push_back(line);
	}

	is >> current_pos_.y >> current_pos_.x;

	cmd_func_map['R'] = &Maze_Traversal::turn_right;
	cmd_func_map['L'] = &Maze_Traversal::turn_left;
	cmd_func_map['F'] = &Maze_Traversal::move_forward;
}

bool Maze_Traversal::cmd_handle(char cmd)
{
	auto it = cmd_func_map.find(cmd);
    if(it == cmd_func_map.end())
		return false;

	(this->*cmd_func_map[cmd])();

	return true;
}

void Maze_Traversal::turn_right()
{
	current_pos_.dir = static_cast<direction_t>((static_cast<int>(current_pos_.dir) + 1) % 4);
}

void Maze_Traversal::turn_left()
{
	current_pos_.dir = static_cast<direction_t>((static_cast <int> (current_pos_.dir) + 3) % 4);
}

void Maze_Traversal::move_forward()
{
	static std::map<direction_t, move_position_t> move_table =
		{{direction_t::east, {1, 0}},
		 {direction_t::south, {0, 1}},
		 {direction_t::west, {-1, 0}},
		 {direction_t::north, {0, -1}}};

	int next_x = current_pos_.x + move_table[current_pos_.dir].move_x;
	int next_y = current_pos_.y + move_table[current_pos_.dir].move_y;

    if (maze[next_y-1][next_x-1] == '*')
        return;
    else
    {
		current_pos_.x = next_x;
		current_pos_.y = next_y;
    }	 
}

position_t Maze_Traversal::get_position()
{
	return current_pos_;
}

void print_the_result(std::ostream & os, const position_t &position)
{
	std::map<direction_t, char> direction_table =
		{{direction_t::east, 'E'},
		 {direction_t::south, 'S'},
		 {direction_t::west, 'W'},
		 {direction_t::north, 'N'}};

	os << position.y << " " << position.x << " " 
		<< direction_table[position.dir] << std::endl;
}

void resolve_uva(std::istream & is, std::ostream & os)
{
	int num; 

	is >> num;

	for (int i=0; i<num; i++)
	{
		char cmd;

		Maze_Traversal maze_traversal(is);

		while ( is >> cmd )
		{
			if (maze_traversal.cmd_handle(cmd) == false)
				break;
		}
		auto position = maze_traversal.get_position();

		if (i > 0)
			os << std::endl;

		print_the_result(os, position);
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
