//game.cpp
//@author Xinyi Gong<gongxinyi@wustl.edu> , Yuan Gao<gao.yuan@wustl.edu> , Kunyao Liu<kunyao.liu@wustl.edu>
//This cpp implements a game class.

#include "stdafx.h"
#include "game.h"
#include "Player.h"
#include "FiveCardDraw.h"
#include <string>
#include <iostream>

using namespace std;

shared_ptr<game> game::gamePtr = nullptr;    //initialize the gamePtr as nullptr

/*
This function returns a gamePtr copy.
*/
shared_ptr<game> game::instance() {
	if (gamePtr == nullptr) {										
		throw instance_not_available;						
	}
	else {
		shared_ptr<game> result = gamePtr;
		return result;		//return a copy of gamePtr
	}
	
};

/*
This function dynamically allocate a game to the gamePtr.
*/
void game::start_game(const string& str) {
	if (gamePtr != nullptr) {
				throw game_already_started;
	}
	else {
		size_t pos = str.find("FiveCardDraw");			//find if str contains FiveCardDraw     -- FiveCardDraws should work.
		if (pos == string::npos) {						//didn't find matched word.
				throw unknown_game;
		}
		else {
			try {
				gamePtr = make_shared<FiveCardDraw>();             //store fivecarddraw game to the static member gamePtr
			}
			catch (...) {
				throw start_game_share_pointer;
			}
			
		}
	}
};

size_t game::player_num() {   
	return this->gamePlayer.size();
}

/*
This function stops the game by clearing the gamePtr.
Because gamePtr is a shared_ptr, the fiveCardDraw object that it is pointing to is also deleted.
*/
void game::stop_game() {
	if (gamePtr == nullptr) {
		throw no_game_in_progress;			//throw error    where to catch
	}
	else {
		gamePtr = nullptr;     						//delete gamePtr 
	}
}

/*
This function checks for duplicate names.
If name is not found in gamePlayer, dynamically allocate it to the gamePlayer vector.
*/
int game::add_player(const string& str) {
	bool isPresent = false;
	for (auto i : gamePlayer) {
		if (i->pName == str){
			isPresent = true;
			
		}
	}
	if (isPresent) {
		throw ignore_this_bad_input;                   //catch when add_player in after_round
	}
	else {
		char *joinPlayer = (char*)str.c_str();				//cast a const string to a non-const char*
		gamePlayer.push_back(make_shared<Player>(joinPlayer));
		
		return success;
	}

	
}

/*
This the player is in the game, return a pointer that points to that player
If not, return nullptr.
*/
shared_ptr<Player> game::find_player(const string& str) {
	bool isPresent = false;
	for (auto i : gamePlayer) {
		if (i->pName == str){
			isPresent = true;
			return i;
		}
	}
	return nullptr;               //return a singular shared_ptr
	
}

game::~game(){}
