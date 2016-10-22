//Player.cpp
//@author Xinyi Gong<gongxinyi@wustl.edu> , Yuan Gao<gao.yuan@wustl.edu> , Kunyao Liu<kunyao.liu@wustl.edu>
//This file implements a player class.


#include "stdafx.h"
#include "Player.h"
#include "hand.h"
#include <string>
#include <vector>
#include <random>
#include <fstream>
#include <sstream>
using namespace std;

/*
Constructor that takes in a c stype string.
*/
Player::Player(char* playername) {
	pName = string(playername);      //set default values.
	win = 0;
	loss = 0;

	//check if this player is automated
	if (pName.back() == '*'){
		pAuto = true;
		int positionP = pName.length();
		pName = pName.substr(pstart, (positionP - pbefore));
	}

	//try to open a file
	ifstream file;
	string filename = pName + ".txt";
	file.open(filename);
	if (!file.is_open()) {
		win = 0;				//reset the values according to the instruction..
		loss = 0;                    
	}
	else {   //successfully open a file.

			while (file) {
				string line_space;
				getline(file, line_space);		//get line until space
				stringstream line_space_;
				line_space_ << line_space;
				string line_comment;
				getline(line_space_, line_comment, '/');		//get line until comment
				istringstream line(line_comment);
				
				line >> pName;   //read in the name.
				int tempWin;
				line >> tempWin;     //try to read in an positive int as win.
				if (tempWin < 0) {
					win = 0;
					loss = 0;
				}
				else {
					win = tempWin;
					int tempLoss;
					line >> tempLoss;		//try to read in an positive int as loss
					if (tempLoss < 0) {      //if one of the wins and losses are invalid numbers, reset both as 0.
						loss = 0;
						win = 0;
					}
					else {
						loss = tempLoss;
					}
				}

			}
			file.close();
		
	}

}

/*
This function prints out a player's info.
*/
ostream& operator<< (ostream& os, const Player& p) {
	os << p.pName << " " << p.win << " " << p.loss;
	return os;
};

/*
This function compares two players.
Returns true only if two players have exactly the same name.
*/
bool operator== (const Player& a, const Player& b) {
	return ((a.pName == b.pName) && (a.win == b.win) && (a.loss == b.loss) && (a.pHand == b.pHand));
};

