//playingCard.cpp
//@author Xinyi,Gong<gongxinyi@wustl.edu>
//This file contains the main funtion and function that reads file and convert the words to Card type

#include "stdafx.h"
#include "card.h"

#include <vector>
#include <fstream>
#include <sstream>

int readFile(vector<Card> &store_list, char *file_name);
int printAllString(const vector<Card> &c);
int usageMessage();
string getSuit(Card a);
string getRank(Card b);
void createNewCard(string l, vector<Card> &o, int u);

int invalid_file_name = 1;
int invalidArgument = -2;


Card::Card(){

}
Card::Card(Suit s, Rank r) {   
	suit = s;
	rank = r;
}

int main(int argc, char *argv[])
{
	if (argc == 2) { //JK Don't hardcode constants
		vector<Card> cardList;
		int result;
		result = readFile(cardList, argv[1]);
		if (result == 0) {//JK Don't hardcode constants
			return printAllString(cardList);
		}
		return result;
	}
	else {
		return usageMessage();
	}


}


int readFile(vector<Card> &store_list, char *file_name) {
	ifstream file;
	file.open(file_name);

	if (file.is_open()) {
		while (file) {
			string line_1, card_1;
			getline(file, line_1);
			istringstream isCard(line_1);

			for (card_1; isCard >> card_1;) {    //iterate over words in a line.

				int card_length = card_1.length();
				if (card_length == 2 || card_length == 3) {         //a valid card can only have a length of 2 or 3. //JK Don't hardcode constants
					createNewCard(card_1, store_list, card_length); //createNewCard function will push valid card to the store_list.
				}
				else {
					cout << card_1 << " is an invalid card" << endl; //invalid card. Print out the error message and then continue.
					continue;
				}
			}

		}
		file.close();
		return 0;
	}

	else {
		cout << "cannot find the file" << endl;
		return invalid_file_name;
	}


}


void createNewCard(string cardInput, vector<Card> &list_output, int card_string_length) {
	Rank newRank = Rank::RANK_ERROR;    //set default rank as error; 
	Suit newSuit = Suit::SUIT_ERROR;	//set default suit as error;

	if (card_string_length == 2) {
		if (cardInput.at(0) == '2') newRank = Rank::two;
		if (cardInput.at(0) == '3') newRank = Rank::three;
		if (cardInput.at(0) == '4') newRank = Rank::four;
		if (cardInput.at(0) == '5') newRank = Rank::five;
		if (cardInput.at(0) == '6') newRank = Rank::six;
		if (cardInput.at(0) == '7') newRank = Rank::seven;
		if (cardInput.at(0) == '8') newRank = Rank::eight;
		if (cardInput.at(0) == '9') newRank = Rank::nine;
		if (tolower(cardInput.at(0)) == 'a') newRank = Rank::ace;
		if (tolower(cardInput.at(0)) == 'j') newRank = Rank::jack;
		if (tolower(cardInput.at(0)) == 'q') newRank = Rank::queen;
		if (tolower(cardInput.at(0)) == 'k') newRank = Rank::king;


		if (tolower(cardInput.at(1)) == 'h') newSuit = Suit::Hearts;
		if (tolower(cardInput.at(1)) == 'c') newSuit = Suit::Clubs;
		if (tolower(cardInput.at(1)) == 'd') newSuit = Suit::Diamonds;
		if (tolower(cardInput.at(1)) == 's') newSuit = Suit::Spades;
	}

	if (card_string_length == 3) {    // if a string has a length of 3, there are only four possibilities for it to be a valid card
		if (cardInput.at(0) == '1' && cardInput.at(1) == '0' && tolower(cardInput.at(2)) == 'h') { newRank = Rank::ten;  newSuit = Suit::Hearts; }
		if (cardInput.at(0) == '1' && cardInput.at(1) == '0' && tolower(cardInput.at(2)) == 'c') { newRank = Rank::ten; newSuit = Suit::Clubs; }
		if (cardInput.at(0) == '1' && cardInput.at(1) == '0' && tolower(cardInput.at(2)) == 'd') { newRank = Rank::ten; newSuit = Suit::Diamonds; }
		if (cardInput.at(0) == '1' && cardInput.at(1) == '0' && tolower(cardInput.at(2)) == 's') { newRank = Rank::ten;  newSuit = Suit::Spades; }
	}

	if (newSuit == Suit::SUIT_ERROR || newRank == Rank::RANK_ERROR) {        //if either suit or rank is an error, then print out the error message
		cout << cardInput << " is an invalid card" << endl;
	}

	else {
		Card w = Card(newSuit, newRank);  //create a new card and push it to the list_output
		list_output.push_back(w);
	}


}


int usageMessage() {
	cout << "ConsoleApplication: You entered an invalid argument" << endl; //JK don't hardcode program name
	cout << "you should enter only one file name follow the name of the executable program" << endl;

	return invalidArgument;
}

string getSuit(Card a) {
	if (a.suit == Suit::Clubs) return "Club";
	else if (a.suit == Suit::Diamonds) return "Diamond";
	else if (a.suit == Suit::Spades) return "Spade";
	else if (a.suit == Suit::Hearts) return "Heart";
	else {
		throw string("invalid card!");;
	}
}

string getRank(Card b){
	if (b.rank == Rank::ace) return "ace";
	else if (b.rank == Rank::two) return "two";
	else if (b.rank == Rank::three) return "three";
	else if (b.rank == Rank::four) return "four";
	else if (b.rank == Rank::five) return "five";
	else if (b.rank == Rank::six) return "six";
	else if (b.rank == Rank::seven) return "seven";
	else if (b.rank == Rank::eight) return "eight";
	else if (b.rank == Rank::nine) return "nine";
	else if (b.rank == Rank::ten) return "ten";
	else if (b.rank == Rank::jack) return "jack";
	else if (b.rank == Rank::queen) return "queen";
	else if (b.rank == Rank::king) return "king";
	else {
		throw string("invalid card!");;
	}
}

int printAllString(const vector<Card> &Card_List) {
	cout << "\n" << endl;
	cout << "Valid cards are" << endl;
	for (auto i : Card_List) {
		cout << getRank(i) << " " << getSuit(i) << endl; //JK catch if you throw something
	}
	return 0;
}





