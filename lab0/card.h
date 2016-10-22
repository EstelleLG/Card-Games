//card.h
//@author Xinyi,Gong<gongxinyi@wustl.edu>
//This file contains the declarations of playingCard function and enum class of Suit and Rank


#ifndef card_H
#define card_H

#include <iostream>
#include <string> 
#include <vector>
#include <map>

using namespace std;


enum class Suit { Diamonds, Hearts, Clubs, Spades, SUIT_ERROR};
enum class Rank { two, three, four, five, six, seven, eight, nine, ten, jack, queen, king, ace, RANK_ERROR};

struct Card {
public:
	Suit suit;
	Rank rank;
	Card();
	Card(Suit s, Rank r);
	int readFile(vector<Card> &c, char *k);
	int printAllString(const vector<Card> &c);
	int usageMessage();
	void createNewCard(string c, vector<Card> &o, int u);
	string Card::getSuit(Card c);
	string Card::getRank(Card c);
	
};


#endif