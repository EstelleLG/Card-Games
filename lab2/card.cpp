#include "stdafx.h"
#include "card.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

Card::Card(){

}
Card::Card(Suit s, Rank r) {
	suit = s;
	rank = r;
}

const bool Card::operator!= (const Card&c) const {
	if (this->suit != c.suit || this->rank != c.rank) {
		return true;
	}
	else {
		return false;
	}
}

const bool Card::operator== (const Card&c) const {
	if (this->suit == c.suit && this->rank == c.rank) {
		return true;
	}
	else {
		return false;
	}
}

const bool Card::operator< (const Card &otherCard) const {
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


const bool Card::operator> (const Card &otherCard) const {
	if (this->rank > otherCard.rank) {
		return true;
	}
	else if ((this->rank == otherCard.rank) && (this->suit > otherCard.suit)){
		return true;
	}
	else {
		return false;
	}
}


