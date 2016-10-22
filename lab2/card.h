#ifndef card_H
#define card_H

#include <iostream>
#include <string> 
#include <vector>
using namespace std;

enum class Suit { Clubs = 1, Diamonds = 2, Hearts = 3, Spades = 4, SUIT_ERROR };
enum class Rank { two = 2, three = 3, four = 4, five = 5, six = 6, seven = 7, eight = 8, nine = 9, ten = 10, jack = 11, queen = 12, king = 13, ace = 14, RANK_ERROR };

enum command_line_arguments { program_name, input_file, shuffle_argument, output_file };
enum command_line_length { one_arguments = 2, two_arguments = 3};
enum command_line_return { no_argument = 1, one_argument_shuffle, two_invalid_arguments, more_than_two_arguments};
enum return_value { success = 0, argument_error = -1, invalid_file_name = -2, invalid_card = -3, not_enough_cards};

enum position_value { first, second, third, fourth, fifth };
enum hand_point { one_pair = 10, two_pairs = 20, three_of_a_kind = 30, straight = 40, flush_ = 50, full_house = 60, four_of_a_kind = 70, straight_flush = 80 };
enum other_number{total_hands = 9, total_cards = 45, hand_size = 5, initialize = 0, count_one_pair = 1, count_two_pairs = 2, count_three = 3, valid_card_length2 = 2, valid_card_length3 = 3 };

struct Card {
public:
	Suit suit;
	Rank rank;
	Card();
	Card(Suit s, Rank r);
	const bool operator!= (const Card&c) const;
	const bool operator== (const Card &) const;
	const bool operator< (const Card &) const;
	const bool operator> (const Card &) const;
};


#endif