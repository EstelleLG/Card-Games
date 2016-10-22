//@author  Xinyi Gong<gongxinyi@wustl.edu>
//This defines a deck class.
#ifndef deck_H
#define deck_H

#include "card.h"
#include "hand.h"
#include <string> 
#include <istream>
#include <ostream> 
#include <iostream>
#include <vector>

using namespace std;


enum iter { iter_start = 0 };
enum deck_error {deck_read_from_file_err = -30 };
class hand;

class deck {
	friend ostream& operator<< (ostream&, const deck&);				
	friend int operator<< (hand&, deck&);	
	friend int operator<< (deck&, deck&);                        
	friend int deal(deck&);
	
private:
	vector<Card> deck_;
public:
	deck();				//lab3: initialize the deck to be empty
	//We can use the default destructor. Since member variable of a deck is a vector of cards. 
	//The destructor of vector will destroy every instances in the vector.
	deck(string);
	int add_card(Card);     //lab3: add a card to a deck. return 0 to indicate success.
	int load(string);
	int shuffle();
	int createNewCard(string cardInput, int card_string_length);
	const int size();
};


#endif