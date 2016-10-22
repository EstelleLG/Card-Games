#include "stdafx.h"

#include "hand.h"
#include "deck.h"
#include "card.h"
#include "rankPoint.h"

#include <vector>
#include <fstream>
#include <sstream>
#include <random> 
#include <istream>
#include <ostream> 
#include <algorithm>

using namespace std;


string getHandSuit(Card a);
string getHandRank(Card b);
rankPoint findRank(const vector<Card> &hands);
bool smaller(int a, int b);
bool larger(int a, int b);

hand::hand(){
	vector<Card> hand_;
}

hand::hand(const hand& d){
	for (auto i : d.hand_) {
		this->hand_.push_back(i);
	}
}

int hand::operator= (const hand& d) {
	this->hand_.clear();
	for (auto i : d.hand_) {
		this->hand_.push_back(i);
	}
	return success;
}

const bool hand::operator == (const hand& d) const {
	bool result = true;
	if (d.size() != this->size()) {
		return false;
	}
	for (int i = 0; i < this->size(); i++) {
		if (this->hand_.at(i) != d.hand_.at(i)) {
			result = false;
		}
	}
	return result;
}

const bool hand::operator < (const hand& d) const {

	for (int i = 0; i < this->size(); i++) {
			if (this->hand_.at(i) < d.hand_.at(i)) {
				return true;
			}
			else if (this->hand_.at(i) > d.hand_.at(i)) {
				return false;
			} 
			//else continue
	}
	return true;
}


const string hand::asString() const{
	string result = "";
	for (auto i : this->hand_) {
		result = result + getHandRank(i) + getHandSuit(i) + " ";
	}
	return result;
}

const int hand::size() const{
	return this->hand_.size();
}

int operator<< (ostream& out, const hand& h) {
	out << h.asString() << endl;
	return success;
}

const bool poker_rank(hand& i, hand&j) {
	vector<Card> &a = i.hand_;
	vector<Card> &b = j.hand_;
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
			if (getHandRank(a[i]) == getHandRank(a[i + 1])) {
				pairA = (int)a[i].rank;
			}
		}
		for (size_t i = 0; i < a.size() - 1; i++) {			//find pair in b hand
			if (getHandRank(b[i]) == getHandRank(b[i + 1])) {
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
		if (getHandRank(a[third]) == getHandRank(a[second])) {
			left = (int)a[first].rank;
		}
		if (getHandRank(a[third]) == getHandRank(a[fourth])) {
			left = (int)a[fifth].rank;
		}
		if (getHandRank(b[third]) == getHandRank(b[second])) {
			leftB = (int)b[first].rank;
		}
		if (getHandRank(b[second]) == getHandRank(b[fourth])) {
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

		if (getHandRank(hands[i]) == getHandRank(hands[i + 1])) {
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

		if (getHandRank(a) == getHandRank(c)) {			//a=b=c
			if (getHandRank(d) == getHandRank(e)) {
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
		if (getHandRank(b) == getHandRank(d)) {    //b=c=d  where it is impossible to have a full house here.
			result = "three of a kind";
			point = three_of_a_kind + scalar * (int)b.rank;
		}

		if (getHandRank(c) == getHandRank(e)) {    //c=d=e 
			if (getHandRank(a) == getHandRank(b)) {
				result = "full house";
				point = full_house + ((int)c.rank + (int)a.rank *scalar)*scalar;
			}
			else {
				result = "three of a kind";
				point = three_of_a_kind + scalar* (int)c.rank;
			}
		}
	}


	if (getHandRank(a) == getHandRank(d) || getHandRank(b) == getHandRank(e)) {     //since the hand is sorted, a=d means a=b=c=d. Similarly, b=e means b=c=d=e.
		result = "four of a kind";
		point = four_of_a_kind + scalar*(int)c.rank;     //the rank of the 4 cards that have the same rank
	}

	if (((int)e.rank - (int)a.rank) == fifth && ((int)d.rank - (int)a.rank) == fourth && ((int)c.rank - (int)a.rank) == third && ((int)b.rank - (int)a.rank) == second) {
		if ((getHandSuit(a) == getHandSuit(b)) && (getHandSuit(b) == getHandSuit(c)) && (getHandSuit(c) == getHandSuit(d)) && (getHandSuit(d) == getHandSuit(e))) {
			result = "straight flush";
			point = straight_flush + (int)e.rank*scalar;          // the rank of the highest card dominates 
		}
		else {
			result = "straight";					// a+1=b b+1=c c+1=d d+1=e
			point = straight + (int)e.rank*scalar;			// the rank of the highest card dominates 
		}
	}


	if ((getHandSuit(a) == getHandSuit(b)) && (getHandSuit(b) == getHandSuit(c)) && (getHandSuit(c) == getHandSuit(d)) && (getHandSuit(d) == getHandSuit(e))) {
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


string getHandSuit(Card a) {
	if (a.suit == Suit::Clubs) return "c";
	else if (a.suit == Suit::Diamonds) return "d";
	else if (a.suit == Suit::Spades) return "s";
	else if (a.suit == Suit::Hearts) return "h";
	else {
		return string("invalid card!");;
	}
}

string getHandRank(Card b){
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

bool smaller(int a, int b) {
	return a < b;
}

bool larger(int a, int b) {
	return a > b;
}
