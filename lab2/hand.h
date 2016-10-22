#ifndef hand_H
#define hand_H

#include <iostream>
#include <string> 
#include <vector>
#include "card.h"
#include "deck.h"
using namespace std;
class deck;
class hand {
	friend int operator<< (ostream&, const hand&);
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
	int operator=(const hand&);
	const bool operator == (const hand&) const;
	const bool operator < (const hand&) const;
	const string asString() const;
	const int size() const;
};


#endif