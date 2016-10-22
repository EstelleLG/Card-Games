//card.h
//@author Xinyi,Gong<gongxinyi@wustl.edu>
//This file contains the declarations of playingCard function and enum class of Suit and Rank


#ifndef card_H
#define card_H

#include <iostream>
#include <string> 
#include <vector>

using namespace std;


enum class Suit { Clubs =1, Diamonds = 2, Hearts=3, Spades=4, SUIT_ERROR };
enum class Rank { two =2, three=3, four=4, five=5, six=6, seven=7, eight=8, nine=9, ten=10, jack=11, queen=12, king=13, ace=14, RANK_ERROR};
enum command_line_arguments { program_name, input_file, valid_argument_number, output_file };
enum return_value {success = 0, argument_error = -1, invalid_file_name = -2, invalid_card = -3};
enum position_value {first, second, third, fourth, fifth};
enum hand_point { one_pair = 10, two_pairs = 20, three_of_a_kind = 30, straight = 40, flush_ = 50, full_house = 60, four_of_a_kind = 70, straight_flush = 80 };
enum other_number{ hand_size = 5, initialize = 0, count_one_pair = 1, count_two_pairs = 2, count_three = 3, valid_card_length2 = 2, valid_card_length3 = 3 };

const double scalar = 0.01;

struct Card {
public:
	Suit suit;
	Rank rank;
	Card();
	Card(Suit s, Rank r);
	int readFile(vector<Card> &, char *);
	int printAllString(const vector<Card> &);
	int usageMessage(string, string);
	int createNewCard(string, vector<Card> &, int);
	int setOfFive(const vector<Card> &pokerHand);
	string Card::getSuit(Card c);
	string Card::getRank(Card c);
	bool operator< (const Card &) const;
	bool compareTwoHands(vector<Card> &, vector<Card> &);
	bool smaller(int a, int b);
	bool larger(int a, int b);

	
};


#endif