//@author  Xinyi Gong<gongxinyi@wustl.edu>
//This defines a player class.
#ifndef Player_h
#define Player_h


#include "hand.h"
#include <string>

using namespace std;

enum player_num{ pstart = 0, pbefore = 1, pafter = 1 };

struct Player {
	string pName;
	hand pHand;
	unsigned win;
	unsigned loss;
	Player(char*);
	bool pAuto = false;
	
};

/*
A non-member function that prints out a player's name, wins and losses.
*/
ostream& operator<< (ostream&os, const Player&);

/*
A non-member function that compares two players. 
*/
bool operator== (const Player&, const Player&);              



#endif