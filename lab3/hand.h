//@author  Xinyi Gong<gongxinyi@wustl.edu>
//This defines a hand class.
#ifndef hand_H
#define hand_H

#include "card.h"
#include "rankPoint.h"
#include "deck.h"
#include <iostream>
#include <string> 
#include <vector>


using namespace std;

enum hand_err{ indexOutOfBound = -31 };

class deck;
class hand {
	friend ostream& operator<< (ostream&, const hand&);
	friend int operator<< (hand&, deck&);
	friend const bool poker_rank(hand& i, hand&j);
	friend int deal(deck&);
private:
	vector<Card> hand_;
public:
	hand();
	hand(const hand&);
	//We can use the default destructor. Since member variable of a hand is a vector of cards. 
	//The destructor of vector will destroy every instances in the vector.
	int clearHand();
	int operator=(const hand&);
	int remove_card(size_t);		   //remove card at the given position.
	Card operator[] (size_t);          //operator[] used in lab3. Returns a card at the given position.
	vector<Card> getHand();			//return the private mamber hand_.
	const bool operator == (const hand&) const;
	const bool operator < (const hand&) const;
	const string asString() const;
	const int size() const;
};

rankPoint findRank(const vector<Card> &);
#endif