#include "stdafx.h"

#include "deck.h"
#include "card.h"
#include "hand.h"
#include "time.h"
#include "rankPoint.h"

#include <vector>
#include <random>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <chrono>


using namespace std;


deck::deck(){

}
deck::deck(string filename) {
	this->load(filename);
	//throw exception
}


int operator<< (ostream&, const deck&);
int operator<< (hand&, deck&);
int createNewCard(string , vector<Card> &, int );
int printVector(vector<Card>);
int shuffle();
int load(string);
int usageMessage(string, string, int);
int deal(deck&);
const int size();
string getRank(Card);
string getSuit(Card);
rankPoint find(const vector<Card> &hands);

vector<hand> nine_hands;
int error = -30;

int main(int argc, char* argv[])
{
	try {
		string program = argv[program_name];

		if (argc == one_arguments) {							
			string name = argv[input_file];						//if argc = 1, then the command line argument should be the filename
			if (name == "-shuffle") {
				string message = "Please enter the filename.";
				return usageMessage(program, message, one_argument_shuffle);
			}
			deck a = deck(name);
			cout << a;   //print out the deck
			deal(a);
			return success;
		}
		if (argc == two_arguments) {							//if argc = 2, then one of the arguments should be -shuffle
			string name = argv[input_file];
			string shuffle_ = argv[shuffle_argument];
			if (name != "-shuffle" && shuffle_ != "-shuffle") {
				string message = "You have entered two filenames.";
				return usageMessage(program, message, two_invalid_arguments);
			}
			else if (name == "-shuffle" && shuffle_ == "-shuffle") {
				string message = "You have entered two -shuffle arguments.";
				return usageMessage(program, message, two_invalid_arguments);
			}

			else {
				if (name == "-shuffle") {       //find out which argument is the filename.
					name = shuffle_;
					shuffle_ = "-shuffle";
				}
				deck a = deck(name);
				cout << a;      //print out the deck
				a.shuffle();
				deal(a);
				return success;
			}
		}

		else {			//other invalid command line arguments number
			if (argc < one_arguments) {
				string message = "No command line arguments are given.";
				return usageMessage(program, message, no_argument);
			}
			else {
				string message = "Too many command line arguments.";
				return usageMessage(program, message, more_than_two_arguments);
			}
		}

	}	
	catch (int e) {				//handle the exception thrown by load
		string program = argv[program_name];
		string message = "Can not open the file.";
		return usageMessage(program, message, invalid_file_name);
	}
		
}

int deck::load(string filename) {
	ifstream file;
	file.open(filename);
	vector<Card>& dList = this->deck_;
	if (!file.is_open()) {
		throw error;
	}
	while (file) {
		string line_space;
		getline(file, line_space);		//get line until space
		stringstream line_space_;
		line_space_ << line_space;
		string line_comment;
		getline(line_space_, line_comment, '/');		//get line until comment
		istringstream line(line_comment);

		string card_;
		for (card_; line >> card_;) {		//iterate over words in a line.
			int cardLength = card_.length();
			if (cardLength == valid_card_length2 || cardLength == valid_card_length3) {         //a valid card can only have a length of 2 or 3.
				this->createNewCard(card_, cardLength); //createNewCard function will push valid card to the temp_store_list.
			}
			else {
				cout << card_ << " is an invalid card" << endl; //invalid card. Print out the error message and then continue.
				continue;
			}
		}
	}
	file.close();
	return success;
}

int deck::shuffle() {
	vector<Card> &c = this->deck_;
	unsigned randomNum = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(c.begin(), c.end(), default_random_engine(randomNum));
	return success;
}

const int deck::size() {
	return this->deck_.size();
}

int deck::createNewCard(string cardInput, int card_string_length) {
	Rank newRank = Rank::RANK_ERROR;    //set default rank as error; 
	Suit newSuit = Suit::SUIT_ERROR;	//set default suit as error;

	if (card_string_length == valid_card_length2) {
		if (cardInput.at(first) == '2') newRank = Rank::two;
		if (cardInput.at(first) == '3') newRank = Rank::three;
		if (cardInput.at(first) == '4') newRank = Rank::four;
		if (cardInput.at(first) == '5') newRank = Rank::five;
		if (cardInput.at(first) == '6') newRank = Rank::six;
		if (cardInput.at(first) == '7') newRank = Rank::seven;
		if (cardInput.at(first) == '8') newRank = Rank::eight;
		if (cardInput.at(first) == '9') newRank = Rank::nine;
		if (tolower(cardInput.at(first)) == 'a') newRank = Rank::ace;
		if (tolower(cardInput.at(first)) == 'j') newRank = Rank::jack;
		if (tolower(cardInput.at(first)) == 'q') newRank = Rank::queen;
		if (tolower(cardInput.at(first)) == 'k') newRank = Rank::king;


		if (tolower(cardInput.at(second)) == 'h') newSuit = Suit::Hearts;
		if (tolower(cardInput.at(second)) == 'c') newSuit = Suit::Clubs;
		if (tolower(cardInput.at(second)) == 'd') newSuit = Suit::Diamonds;
		if (tolower(cardInput.at(second)) == 's') newSuit = Suit::Spades;
	}

	if (card_string_length == valid_card_length3) {    // if a string has a length of 3, there are only four possibilities for it to be a valid card
		if (cardInput.at(first) == '1' && cardInput.at(second) == '0' && tolower(cardInput.at(third)) == 'h') { newRank = Rank::ten;  newSuit = Suit::Hearts; }
		if (cardInput.at(first) == '1' && cardInput.at(second) == '0' && tolower(cardInput.at(third)) == 'c') { newRank = Rank::ten; newSuit = Suit::Clubs; }
		if (cardInput.at(first) == '1' && cardInput.at(second) == '0' && tolower(cardInput.at(third)) == 'd') { newRank = Rank::ten; newSuit = Suit::Diamonds; }
		if (cardInput.at(first) == '1' && cardInput.at(second) == '0' && tolower(cardInput.at(third)) == 's') { newRank = Rank::ten;  newSuit = Suit::Spades; }
	}

	if (newSuit == Suit::SUIT_ERROR || newRank == Rank::RANK_ERROR) {        //if either suit or rank is an error, then print out the error message
		cout << cardInput << " is an invalid card" << endl;
		return invalid_card;
	}

	else {
		Card w = Card(newSuit, newRank);  //create a new card and push it to the list_output
		this->deck_.push_back(w);
		//list_output.push_back(w);
		return success;
	}


}

string getSuit(Card a) {
	if (a.suit == Suit::Clubs) return "c";
	else if (a.suit == Suit::Diamonds) return "d";
	else if (a.suit == Suit::Spades) return "s";
	else if (a.suit == Suit::Hearts) return "h";
	else {
		return string("invalid card!");;
	}
}

string getRank(Card b){
	if (b.rank == Rank::ace) return "a";
	else if (b.rank == Rank::two) return "2";
	else if (b.rank == Rank::three) return "3";
	else if (b.rank == Rank::four) return "4";
	else if (b.rank == Rank::five) return "5";
	else if (b.rank == Rank::six) return "6";
	else if (b.rank == Rank::seven) return "7";
	else if (b.rank == Rank::eight) return "8";
	else if (b.rank == Rank::nine) return "9";
	else if (b.rank == Rank::ten) return "10";
	else if (b.rank == Rank::jack) return "j";
	else if (b.rank == Rank::queen) return "q";
	else if (b.rank == Rank::king) return "k";
	else {
		return string("invalid card!");;
	}
}

rankPoint find(const vector<Card> &hands) {
	string result = "no rank";
	double point = initialize;

	Card a = hands[first];
	Card b = hands[second];
	Card c = hands[third];
	Card d = hands[fourth];
	Card e = hands[fifth];


	int count = initialize;
	for (size_t i = 0; i < hands.size() - 1; i++) {						//check how many same elements are there in a hand

		if (getRank(hands[i]) == getRank(hands[i + 1])) {
			count++;
		}
	}

	if (count == count_one_pair) {				//if count == 1, then there is only one pair, since the hand is already sorted.
		result = "one pair";
		point = one_pair;						//Earn points if the hand has some ranks!!  Use compareTwoHands Function to compare 
	}
	else if (count == count_two_pairs || count == count_three) {
		result = "two pairs";					//if count == 2, then there may be two pairs, or full house, or three of a kind. 
		point = two_pairs;						//use compareTwoHands Function to compare

		if (getRank(a) == getRank(c)) {			//a=b=c
			if (getRank(d) == getRank(e)) {
				result = "full house";
				point = full_house + ((int)a.rank + (int)d.rank *scalar)*scalar;    //abc has the same rank. 
				//Full house with larger a/b/c will have higher score. Also, full house with larger d/e will have higher score.
				//But in order to make sure that rank score full house = 60 dominates, then a/b/c dominates, we multiply a scalar = 0.01. 
				//Similar logic applies below.
			}
			else {
				result = "three of a kind";
				point = three_of_a_kind + scalar * (int)a.rank;     //the rank of the 3 cards that have the same rank dominates
			}
		}
		if (getRank(b) == getRank(d)) {    //b=c=d  where it is impossible to have a full house here.
			result = "three of a kind";
			point = three_of_a_kind + scalar * (int)b.rank;
		}

		if (getRank(c) == getRank(e)) {    //c=d=e 
			if (getRank(a) == getRank(b)) {
				result = "full house";
				point = full_house + ((int)c.rank + (int)a.rank *scalar)*scalar;
			}
			else {
				result = "three of a kind";
				point = three_of_a_kind + scalar* (int)c.rank;
			}
		}
	}


	if (getRank(a) == getRank(d) || getRank(b) == getRank(e)) {     //since the hand is sorted, a=d means a=b=c=d. Similarly, b=e means b=c=d=e.
		result = "four of a kind";
		point = four_of_a_kind + scalar*(int)c.rank;     //the rank of the 4 cards that have the same rank
	}

	if (((int)e.rank - (int)a.rank) == fifth && ((int)d.rank - (int)a.rank) == fourth && ((int)c.rank - (int)a.rank) == third && ((int)b.rank - (int)a.rank) == second) {
		if ((getSuit(a) == getSuit(b)) && (getSuit(b) == getSuit(c)) && (getSuit(c) == getSuit(d)) && (getSuit(d) == getSuit(e))) {
			result = "straight flush";
			point = straight_flush + (int)e.rank*scalar;          // the rank of the highest card dominates 
		}
		else {
			result = "straight";					// a+1=b b+1=c c+1=d d+1=e
			point = straight + (int)e.rank*scalar;			// the rank of the highest card dominates 
		}
	}


	if ((getSuit(a) == getSuit(b)) && (getSuit(b) == getSuit(c)) && (getSuit(c) == getSuit(d)) && (getSuit(d) == getSuit(e))) {
		if (((int)e.rank - (int)a.rank) == fifth && ((int)d.rank - (int)a.rank) == fourth && ((int)c.rank - (int)a.rank) == third && ((int)b.rank - (int)a.rank) == second) {
			result = "straight flush";
			point = straight_flush + (int)e.rank*scalar;
		}
		else{
			result = "flush";
			point = flush_;        //use compareTwoHands function to compare. 
		}

	}

	return rankPoint(result, point);
}

int operator<< (ostream& out, const deck& d) {
	for (auto i : d.deck_) {
		out << getRank(i) << getSuit(i) << endl;
	}
	return success;
}

int operator<< (hand&h, deck&d) {		//deal a deck
	h.hand_.push_back(d.deck_.back());
	d.deck_.pop_back();
	sort(h.hand_.begin(), h.hand_.end());
	return success;
}

int deal(deck &a) {
	for (int count = first; count < total_hands; count++) {
		hand empty;
		nine_hands.push_back(empty);
	}

	if (a.size() < total_cards) {
		cout << "There are less than 45 cards." << endl;
		return not_enough_cards;
	}

	else {
		for (unsigned i = 0; i < hand_size; i++) {
			for (unsigned j = 0; j < total_hands; j++) {
				nine_hands.at(j) << a;
			}
		}
	}

	int count = first;
	for (auto i : nine_hands) {
		cout << "Hand " << count << endl;
		cout << i;
		count++;
	}

	if (a.size() != 0) {
		cout << "the rest of the deck has" << endl;
		cout << a;			//print out the rest of the cards in the deck.
	}
	//print out the content of deck??


	cout << "after sorting the hands based on the < operator" << endl;
	sort(nine_hands.begin(), nine_hands.end());
	for (auto i : nine_hands) {
		cout << "\n" << endl;
		cout << i;
		cout << find(i.hand_).getHandRank() << endl;
	}

	cout << "after sorting the hands based on the rank" << endl;
	sort(nine_hands.begin(), nine_hands.end(), poker_rank);
	for (auto i : nine_hands) {
		cout << "\n" << endl;
		cout << i;
		cout << find(i.hand_).getHandRank() << endl;
	}

	return success;
}

int usageMessage(string name, string message, int return_value) {
	cout << "Enter the filename after the name of this program. " << endl;
	cout << "Add an optional '-shuffle' argument to perform shuffle." << endl;
	cout << name << ": " << message << endl;
	return return_value;
}
