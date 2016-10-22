//@author  Xinyi Gong<gongxinyi@wustl.edu>
//This defines a FiveCardDraw class.

#ifndef FiveCardDraw_h
#define FiveCardDraw_h

#include "game.h"


enum Num {start = 0, loop_sstart = 1, suitSize = 4, loopSSize = 5, loop_rstart = 2, rankSize = 13, loopRSize = 15, loopHand = 4, handSize = 5, not_enough_to_deal =135, before = 1, after = 1, 
	probablity_base = 100, lowest_prob = 10, middle_prob = 50, winner_prob = 90, last_person = 1, maximum_player = 10, too_many_players};

class FiveCardDraw: public game{       //derived class
protected:
	size_t dealerPlayer;
	deck discard;              
public:
	FiveCardDraw();
	virtual int before_turn(Player&); //let users to discard cards.
	virtual int turn(Player&);	//deal cards again.
	virtual int after_turn(Player&);   //print out the users' names and hands.
	virtual int before_round();  
	virtual int round();
	virtual int after_round();
};

bool poker(shared_ptr<Player> a, shared_ptr<Player> b);  
string autoDecision(Player &);

#endif
