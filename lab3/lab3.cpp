//lab3.cpp
//@author Xinyi Gong<gongxinyi@wustl.edu> , Yuan Gao<gao.yuan@wustl.edu> , Kunyao Liu<kunyao.liu@wustl.edu>
//This is the main function.

#include "stdafx.h"
#include "deck.h"
#include "card.h"
#include "hand.h"
#include "rankPoint.h"
#include "Player.h"
#include "game.h"
#include "FiveCardDraw.h"


#include <sstream>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>

int usageMessage(string, string, int);

int main(int argc, char* argv[])
{
	//check command_line_argument
	if (argc < min_argument) {
		string program = argv[program_name];
		string message = "The program should be run with at least 3 arguments: the name of a game, and the names of two or more players";   
		return usageMessage(program, message, less_than_three_arguments);
	}
	if (argc > maximum_arguments){
		return usageMessage(argv[program_name], "too many players", not_enough_to_deal);
	}
	else { 
		try {
			string gamename = argv[first_argument];
			game::start_game(gamename);					//check if the first_argument contains FiveCardDraw inside this function.
			shared_ptr<game> pointerToGame = game::instance();	

			//add players to the game
			for (int i = first_player; i < argc; i++){
				pointerToGame->add_player(argv[i]);        //if the command line arguments contain the same name, add_player will ignore it and continue;
			}

			cout << "game started" << endl;
			
			while (pointerToGame->player_num() >= min_player)   //check if gamePlayer >=2
			{
				pointerToGame->before_round();
				int roundResult = (*pointerToGame).round();
				if (roundResult != success){
					throw roundResult;						//not enough cards to deal exception (maindeck+discard < cards needed)
				}
				pointerToGame->after_round();
			} 
			
			game::stop_game();
			cout << "Game Over! There are not enough players." << endl;
			
			return success;

		}

		catch (...) {
			try{
				game::stop_game();					//try stop_game
				return usageMessage(argv[program_name], "Exception caught", exception_error);
			}
			catch (...) {
				return usageMessage(argv[program_name], "Exception caught", exception_error);
			}
		}
	}

	
}

int usageMessage(string name, string message, int return_value) {
	cout << name << ": " << message << return_value << endl;
	return return_value;
}
