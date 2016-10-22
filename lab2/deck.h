#ifndef deck_H
#define deck_H

#include <istream>
#include <ostream> 
#include <iostream>
#include <string> 
#include <vector>
#include "card.h"
#include "hand.h"

//using namespace std;
class hand;

class deck {
	friend int operator<< (std::ostream&, const deck&);
	friend int operator<< (hand&, deck&);
	friend int deal(deck&);
	
private:
	vector<Card> deck_;
public:
	deck();
	//We can use the default destructor. Since member variable of a deck is a vector of cards. 
	//The destructor of vector will destroy every instances in the vector.
	deck(string);
	int load(string);
	int shuffle();
	const int size();
	int createNewCard(string cardInput, int card_string_length);

};





#endif