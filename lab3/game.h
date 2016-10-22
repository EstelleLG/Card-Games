//@author  Xinyi Gong<gongxinyi@wustl.edu>
//This defines a game abstract class.
#ifndef game_h
#define game_h

#include "Player.h"
#include <memory>
#include <string>
#include <iostream>
using namespace std;
enum error{ start_game_share_pointer = 99, instance_not_available = 20, game_already_started, unknown_game, no_game_in_progress, already_playing, ignore_this_bad_input};
enum mainFunction_num {first_player = 2, min_player = 2, maximum_arguments = 12, exception_error = 40, min_argument = 4};

class game{
protected:
	static shared_ptr<game> gamePtr;		
	deck gameDeck;
	vector<shared_ptr<Player>>  gamePlayer;
public: 
	static shared_ptr<game> instance();      //returns a copy of the static gamePtr
	static void start_game(const string&);	
	static void stop_game();
	int add_player(const string&);
	size_t player_num();
	shared_ptr<Player> find_player(const string&);
	virtual ~game();                          //virtual destructor
	virtual int before_turn(Player&) = 0;
	virtual int turn(Player&) = 0;
	virtual int after_turn(Player&) = 0;
	virtual int before_round() = 0;
	virtual int round() = 0;
	virtual int after_round() =0;
};




#endif


