//playingCard.cpp
//@author Xinyi,Gong<gongxinyi@wustl.edu>
//This file contains the main funtion and function that reads cards and find the hand

#include "stdafx.h"
#include "card.h"
#include "rankPoint.h"

#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

bool compareTwoHands(vector<Card> &a, vector<Card> &b);
bool smaller(int a, int b);
bool larger(int a, int b);
int readFile(vector<Card> &store_list, char *file_name);
int printAllString(const vector<Card> &c);
int usageMessage(string, string);
int setOfFive(const vector<Card> &pokerHand);
int createNewCard(string l, vector<Card> &o, int u);
string getSuit(Card a);
string getRank(Card b);
rankPoint findRank(const vector<Card> &hands);
vector<vector<Card>> rankList;


Card::Card(){

}
Card::Card(Suit s, Rank r) {   
	suit = s;
	rank = r;
}

bool Card::operator< (const Card &otherCard) const {
	if (this->rank < otherCard.rank) {
		return true;
	}
	else if ((this->rank == otherCard.rank) && (this->suit < otherCard.suit)){
		return true;
	}
	else {
		return false;
	}
}

bool smaller(int a, int b) {
	return a < b;
}

bool larger(int a, int b) {
	return a > b;
}



int main(int argc, char *argv[])
{
	if (argc == valid_argument_number) { 
		vector<Card> cardList;
		int result;
		result = readFile(cardList, argv[input_file]);
		if (result == success) {
			setOfFive(cardList);					//read a set of five cards into vector<vector<card>> ranklist. Each has a size of five.
			sort(cardList.begin(), cardList.end());				//sort all the cards
			sort(rankList.begin(), rankList.end(), compareTwoHands);    //sort all the hands
			
			for (auto i : rankList) {				//print out each hand in order
				cout << "This hand has a " << findRank(i).getHandRank() << endl;
			}
			printAllString(cardList);				//print out the sorted cards
		}
		return result;
	}
	else {
		string message = "you should enter only one file name just following the name of the program";
		return usageMessage(argv[program_name], message);
	}

}

bool compareTwoHands(vector<Card> &a, vector<Card> &b) {                 // compare two hands' ranks.  
	rankPoint aHand = findRank(a);
	rankPoint bHand = findRank(b);
	if (aHand.getPoint() < bHand.getPoint()) {      //compare different ranks using points.
		return true;
	}
	string aRank = aHand.getHandRank();
	string bRank = bHand.getHandRank();

	if ((aRank == bRank) && (bRank == "no rank")) {
		bool result = false;									// if both two hands don't have rank, compare from the highest digit to lowest digit.
		result = smaller((int)a[first].rank, (int)b[first].rank);
		result = smaller((int)a[second].rank, (int)b[second].rank);
		result = smaller((int)a[third].rank, (int)b[third].rank);
		result = smaller((int)a[fourth].rank, (int)b[fourth].rank);
		result = smaller((int)a[fifth].rank, (int)b[fifth].rank);

		return result;

	}
	if (aRank == bRank && bRank == "one pair") {
		int pairA;
		int pairB;
		for (size_t i = 0; i < a.size() - 1; i++) {         //find pair in a hand.
			if (getRank(a[i]) == getRank(a[i + 1])) {
				pairA = (int)a[i].rank;
			}
		}
		for (size_t i = 0; i < a.size() - 1; i++) {			//find pair in b hand
			if (getRank(b[i]) == getRank(b[i + 1])) {
				pairB = (int)b[i].rank;
			}
		}

		if (smaller(pairA, pairB)) {						//compare two hands using the only pair
			return true;
		}
		if (larger(pairA, pairB)) {						
			return false;
		}
		else {												//only two hands with the same rank remain unhandled.
			bool ans = false;								//loop over all the other three elements, from 4 to 0.
			ans = smaller((int)a[first].rank, (int)b[first].rank);
			ans = smaller((int)a[second].rank, (int)b[second].rank);
			ans = smaller((int)a[third].rank, (int)b[third].rank);
			ans = smaller((int)a[fourth].rank, (int)b[fourth].rank);
			ans = smaller((int)a[fifth].rank, (int)b[fifth].rank);

			return ans;
		}
	}


	if (aRank == bRank && bRank == "two pair") {
		int firstPair = (int)a[second].rank;
		int secondPair = (int)a[fourth].rank;
		int left = (int)a[third].rank;
		int firstPairB = (int)b[second].rank;
		int secondPairB = (int)b[fourth].rank;
		int leftB = (int)b[third].rank;
		
		//find out two pairs and the left element in both A hand and B hand.
		if (getRank(a[third]) == getRank(a[second])) {
			left = (int)a[first].rank;
		}
		if (getRank(a[third]) == getRank(a[fourth])) {
			left = (int)a[fifth].rank;
		}
		if (getRank(b[third]) == getRank(b[second])) {
			leftB = (int)b[first].rank;
		}
		if (getRank(b[second]) == getRank(b[fourth])) {
			leftB = (int)b[fifth].rank;
		}


		if (smaller(secondPair, secondPairB)) {			//first compare the second pair. 
			return true;
		}	
		if (larger(secondPair, secondPairB)) {			
			return false;
		}
		if (smaller(firstPair, firstPairB)) {			//then compare the first pair
			return true;
		}
		if (larger(firstPair, firstPairB)) {
			return false;
		}
		if (smaller(left, leftB)) {						//then compare what is left over. 
			return true;
		}

	}
	if (aRank == bRank && bRank == "flush") {			//for two hands of flush, compare the highest element, and then the next highest element.
		for (size_t i = a.size(); i > 0; i--){
			if (a[i - 1].rank < b[i - 1].rank) {
				return true;
			}
		}
	}

	return false;

}

int readFile(vector<Card> &store_list, char *file_name) {
	ifstream file;
	file.open(file_name);

	if (file.is_open()) {
		vector<Card> temp_store_list;
		while (file) {
			string line_1, card_1, Line;
			getline(file, line_1);				//get line until space
			stringstream line_2;
			line_2 << line_1;
			getline(line_2, Line, '/');			//get line until comment/
			istringstream isCard(Line);

			for (card_1; isCard >> card_1;) {    //iterate over words in a line.

				int card_length = card_1.length();
				if (card_length == valid_card_length2 || card_length == valid_card_length3) {         //a valid card can only have a length of 2 or 3.
					createNewCard(card_1, temp_store_list, card_length); //createNewCard function will push valid card to the temp_store_list.
				}
				else {
					cout << card_1 << " is an invalid card" << endl; //invalid card. Print out the error message and then continue.
					continue;
				}
			}
			if (temp_store_list.size() == hand_size) {     //check too few or too many cards in a hand
				//cout << "valid hand" << endl;

				for (auto i : temp_store_list) {	// if the valid is valid, push it to the store_list
					store_list.push_back(i);
				}

			}
			else {
				cout << "invalid hands" << endl;     //print out the warning message if it's not a valid hand.
			}
			temp_store_list.clear();			//clear the temp_store_list to store the next line. 
		}
		file.close();
		return success;
	}

	else {
		cout << "cannot find the file" << endl;
		return invalid_file_name;
	}


}


int setOfFive(const vector<Card> &pokerHand){
	
	vector<Card> fiveCards;
	for (size_t i = 0; i < pokerHand.size(); i += hand_size) {		//read in 5 cards at a time. 
		fiveCards.push_back(pokerHand[i]);
		fiveCards.push_back(pokerHand[i + second]);
		fiveCards.push_back(pokerHand[i + third]);
		fiveCards.push_back(pokerHand[i + fourth]);
		fiveCards.push_back(pokerHand[i + fifth]);
		sort(fiveCards.begin(), fiveCards.end());					//sort the five cards before we determine the rank
		//cout << "This hand has " << findRank(fiveCards).getHandRank() << endl;        //for extra credits part, comment this out.
		rankList.push_back(fiveCards);								//push this sorted five cards to the rankList.
		fiveCards.clear();											//clear and wait to read in the next five cards.
	}
	return success;
}


rankPoint findRank(const vector<Card> &hands) {
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

int createNewCard(string cardInput, vector<Card> &list_output, int card_string_length) {
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
		list_output.push_back(w);
		return success;
	}


}


int usageMessage(string name, string message) {
	cout << name << " " << message << endl;
	return argument_error;
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

int printAllString(const vector<Card> &Card_List) {
	cout << "\n" << endl;
	cout << "Valid cards are" << endl;
	for (auto i : Card_List) {
		cout << getRank(i) << getSuit(i) << endl; 
	}
	return success;
}





