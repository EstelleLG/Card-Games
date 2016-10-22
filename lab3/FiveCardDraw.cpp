//FiveCardDraw.cpp
//@author Xinyi Gong<gongxinyi@wustl.edu> , Yuan Gao<gao.yuan@wustl.edu> , Kunyao Liu<kunyao.liu@wustl.edu>
//This cpp implements a game called FiveCardDraw

#include "stdafx.h"
#include "game.h"
#include "deck.h"
#include "FiveCardDraw.h"
#include "card.h"
#include "hand.h"
#include "Player.h"
#include "rankPoint.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <memory>
#include <vector>
#include <stdio.h>
#include <stdlib.h>     
#include <time.h>  
using namespace std;


/*
Constructor that initializes dealerPlayer to be 0;
*/
FiveCardDraw::FiveCardDraw() {
	dealerPlayer = 0; 

	for (int s = loop_sstart; s < loopSSize; s++) {      //add 52 cards to the deck
		for (int r = loop_rstart; r < loopRSize; r++) {
			Card temp = Card(Suit(s), Rank(r));            
			gameDeck.add_card(temp);
		}
	}

};

/*
Virtual before_turn method that prompt the user to discard cards.
*/
int FiveCardDraw::before_turn(Player& player) {
	while (true) {
		cout << "" << endl;
		cout << "Name: " << player.pName << " Hand: " << player.pHand << endl;
		cout << "Which card do you want to discard? " << endl;
		cout << "Enter 'no cards', 'all cards', or index of cards(1 - 5) seperated by spaces." << endl;
		string sen;
		
		//if the player is automated player, call autoDecision function which returns a string that represent which cards are discarded
		if (player.pAuto) {
			sen = autoDecision(player);
		}
		else {
			getline(cin, sen);
		}



		if (sen == "no cards") {
			return success;     //do nothing and break from the while loop.        
		}
		if (sen == "all cards") {
			for (int i = loopHand; i >= 0 ; i--) {
				discard.add_card(player.pHand[i]);
				player.pHand.remove_card(i);            //use size_t instead of the iterator 
			}
			return success;   //break from the while loop
		}
		istringstream otherInput(sen);
		string num;
		vector<size_t> index;

		bool validIndex = true;   //check if the input has any invalid index number. If there is any invalid input, reprompt the user to enter a valid input.
		for (num; otherInput >> num;) {
			if (num == "1" || num == "2" || num == "3" || num == "4" || num == "5") {
				validIndex = true && validIndex;
				auto i = find(index.begin(), index.end(), stoi(num));
				if (i == index.end()){
					index.push_back(stoi(num));
				}
			}
			else {
				validIndex = false;
			}
		}

		if (validIndex) {								//if all input numbers are valid index
			if (index.size() < handSize){				//check the size of index vector.   If the size of index >= handSize, reprompt the user to enter a valid input. 
				sort(index.begin(), index.end());		//sort the index
				reverse(index.begin(), index.end());
				for (auto i : index){                                   //use iterator to delete the index from the last card to the first card in a hand. (In order to keep the index correct.)
					unsigned toBeDel = i - before;
					discard.add_card(player.pHand[toBeDel]);
					player.pHand.remove_card(toBeDel);			//use size_t instead of the iterator.
				}
				return success;					//successfully delete. Break from the while loop.
			}
		}

	}


	return success;
};

/*
This function determines which card should a automated player throw based on his hand.
Returns a valid string - "no cards", "all cards" or card indexs.
*/
string autoDecision(Player & player) {
	string decision = "";

	vector<Card> h = player.pHand.getHand();
	string pAutoRank = findRank(h).getHandRank();
	if (pAutoRank == "straight flush" || pAutoRank == "straight" || pAutoRank == "flush" || pAutoRank == "full house"){
		decision = "no cards";
	}
	if (pAutoRank == "four of a kind"){
		if (h[first].rank == h[fourth].rank){
			decision = "5";
		}
		else decision = "1";
	}
	if (pAutoRank == "two pairs") {
		if ((h[second].rank == h[third].rank) && (h[fourth].rank == h[fifth].rank)) {  //x aa bb
			decision = "1";
		}
		else if ((h[first].rank == h[second].rank) && (h[fourth].rank == h[fifth].rank)){ //aa x bb
			decision = "3";
		}
		else {  // aabb x
			decision = "5";
		}
	}
	if (pAutoRank == "three of a kind"){
		if (h[first].rank == h[third].rank){
			decision = "4 5";
		}
		else if (h[second].rank == h[fourth].rank){
			decision = "1 5";
		}
		else decision = "1 2";
	}
	if (pAutoRank == "one pair"){
		if (h[first].rank == h[second].rank){
			decision = "3 4 5";
		}
		else if (h[second].rank == h[third].rank){
			decision = "1 4 5";
		}
		else if (h[third].rank == h[fourth].rank){
			decision = "1 2 5";
		}
		else decision = "1 2 3";
	}

	if (pAutoRank == "no rank"){     
		if (h[fifth].rank == Rank::ace){
			decision = "1 2 3 4";
		}
		else decision = "1 2 3";
	}


	return decision;
}


/*
A virtual function that deals the card again.
*/
 int FiveCardDraw::turn(Player & player){
	 unsigned thrown = handSize - player.pHand.size();     //thrown num    
	 unsigned mainDeckSize = gameDeck.size();
	 unsigned discardSize = discard.size();
	 if (mainDeckSize + discardSize < thrown){
		 return not_enough_to_deal;								
	 }
	 if (mainDeckSize < thrown){ //get some from gameDeck, and get the rest of cards from discard
		 unsigned fromDisc = thrown - mainDeckSize;
		 discard.shuffle();
		 for (unsigned i = initialize; i < mainDeckSize; i++){
			 player.pHand << gameDeck;
		 }
		 for (unsigned i = initialize; i < fromDisc; i++){
			 player.pHand << discard;
		 }
	 }
	 else {				//gameDeck has enough card to deal.
		 for (unsigned i = initialize; i < thrown; i++){
			 player.pHand << gameDeck;
		 }
	 }
	 return success;

 };

 /*
 This function prints out a player's name and hand.
 */
 int FiveCardDraw::after_turn(Player& player) {
	 cout << "Name: "<< player.pName << endl;
	 cout << "Hand: "<< player.pHand << endl;
	 return success;
 }

 /*
 This function deals cards to every players until everyone in this game gets 5 cards in his hand.
 */
 int FiveCardDraw::before_round() {
	
	 gameDeck.shuffle();      //shuffle the deck before every round.
	 int playerSize = gamePlayer.size();              
	 int currentPos = dealerPlayer+after;     //starting position

	 for (int i = initialize; i < handSize; i++) {
		 while (currentPos != dealerPlayer) {				//loop over everyone except dealerPlayer
			 if (currentPos < playerSize) {			
				gamePlayer[currentPos]->pHand << gameDeck;
				 currentPos++;								//update the currentPos
			 }
			 else {
				 currentPos = start;							//update the currentPos (currentPos > playerSize, set currentPos back to 0)
			 }
		 }
		 gamePlayer[currentPos]->pHand << gameDeck;    //currentPos == dealerPlayer after this while loop
		 currentPos++;									//update the currentPos to be the next one after the dealerPlayer,  and start the next for loop. 
	 }

	 for (auto i : gamePlayer) {
		 before_turn(*i);      //i is a share_ptr to a player
	 }

	 return success;
 }


 /*
 This function loops over each player and call turn function.
 if turn function returns success, call after_turn on this player.
 */
 int FiveCardDraw::round(){
	 for (auto i : gamePlayer) {
		 int result = turn(*i);
		 if (result != success) {
			 return result;
		 }
		 after_turn(*i);
	 }
	 return success;
 }

 /*
 This function compares two players' hands by calling poker_rank function defined in hand.cpp.
 */
 bool poker(shared_ptr<Player> a,shared_ptr<Player> b) {
	 if (a == nullptr) {
		 return false;
	 }
	 if (b == nullptr) {
		 return true;
	 }
	 else {
		 return poker_rank(a->pHand, b->pHand);          
	 }
 }

 /*
 This function:
 1.Sorts players' hands and updates the players' record. 
 2. Moves all cards to gameDeck.
 3. Asks if any player want to quit or join.
 */
 int FiveCardDraw::after_round() {
	vector<shared_ptr<Player>>  temp = gamePlayer;         //copy of gamePlayer
	sort(temp.begin(), temp.end(), poker);                  //override poker_rank function

	Player winner = *temp[temp.size()-before];          //winner now is the last person in the temp vector.
	Player lowest = *temp[first];

///////print out the sorted 
	cout << "" << endl;
	cout << "The result is " << endl;
	for (auto eachPlayer : temp) {
		if (*eachPlayer == winner) {
			eachPlayer->win++;
		}
		else {
			eachPlayer->loss++;
		}
		cout << *eachPlayer << endl;                   
		cout << eachPlayer->pHand << endl;
	}

//////move all phands and discarded cards to gameDeck
	for (auto eachPlayer : gamePlayer) {
		for (auto i = 0; i < eachPlayer->pHand.size(); i++){
			gameDeck.add_card(eachPlayer->pHand[i]);
		}
		eachPlayer->pHand.clearHand();
	}
	//clear the deck
	gameDeck << discard;        //defined operator


//////Determine if an automated player wants to quit
	unsigned calcProb;
	vector<shared_ptr<Player>>::iterator eachPlayer = gamePlayer.begin();
	while (eachPlayer != gamePlayer.end()) {
		if ((*eachPlayer)->pAuto ) {
			srand(time(0));
			unsigned probability = (unsigned)rand() % probablity_base;    //generate a random unsigned from 0 to 99 for every autoplayer
			//if the auto player is a winner 
			if ((*eachPlayer)->pName == winner.pName) {			//since we don't allow duplicate names, we can compare pName
				calcProb = winner_prob;
			}
			//if the auto player is the lowest
			else if ((*eachPlayer)->pName == lowest.pName) {
				calcProb = lowest_prob;
			}
			else {
				calcProb = middle_prob;
			}

			//quit if probablity > calcProb, otherwise, remain in the game.
			if (probability > calcProb) {
				cout << "Automated player: "<< (*eachPlayer)->pName << " decided to quit" << endl;

				//write an output file
				std::ofstream ofs((*eachPlayer)->pName + ".txt", std::ofstream::out);
				ofs << **eachPlayer;   
				ofs.close();

				eachPlayer = gamePlayer.erase(eachPlayer);
			}
			else {
				eachPlayer++;
			}
		}
		else {
			eachPlayer++;
		}
	}



//////ask if any users want to quit
		while (true) {
			cout << "Does anyone want to quit the game? Please enter 'yes' or 'no' " << endl;
			string answer;
			getline(cin, answer);
			if (answer == "yes") {
				cout << "Enter your usernames(seperated by spaces)" << endl;				
				string addUsers;
				getline(cin, addUsers);
				istringstream stream(addUsers);
				string stringA;
				for (stringA; stream >> stringA;) {
					auto findP = gamePlayer.begin();
					while (findP != gamePlayer.end()) {
						if ((*findP)->pName == stringA) {
							//write a file
							std::ofstream ofs(stringA + ".txt", std::ofstream::out);
							ofs << **findP;   
							ofs.close();

							auto i = gamePlayer.begin();
							while (i != gamePlayer.end()) {
								if (**i == **findP) {
									gamePlayer.erase(findP);          //iterator to that object to be removed
									break;  //end of finding findP in gamePlayer
								}
								++i;
							}
							break; //end of while loop finding target player

						}
						++findP;
					}
				}
				break;    //end of processing all words in stream
				//if there is any invliad input, we ignore it and break from the while loop.

			}
			else if (answer == "no") {
				break;     //break from while loop
			}

	}

//////ask if any player want to join
	if (gamePlayer.size() < maximum_player) {     //only ask users to join when there are less than 10 players in the game 
													//not_enough_cards_to_deal
		while (true) {
			cout << "Does anyone want to join the game? Please enter 'yes' or 'no' " << endl;
			string enterAns;
			getline(cin, enterAns);
			if (enterAns == "yes") {
				cout << "Enter the names of newusers (seperate by spaces) " << endl;
				string enteredUsers;
				getline(cin, enteredUsers);
				istringstream inputStream(enteredUsers);
				string newName;
				for (newName; inputStream >> newName;) {
					//check for duplicate     
					try{
						if (gamePlayer.size() < maximum_player) {
							this->add_player(newName);
						}
						else {
							throw too_many_players;
						}
					}
					catch (...){
						//continue;
					}
				}
				break;
			}
			else if (enterAns == "no") {
				break;
			}

		}
	}


//////increment the dealer member variable to the next player position(or to 0 
	dealerPlayer++;
	if (dealerPlayer >= gamePlayer.size()) {
		dealerPlayer = first;
	}

/////if gamePlayer.size() = 1, the game will end in the main function
/////update the last person's file
	if (gamePlayer.size() == last_person) {
		string filename =  gamePlayer[first]->pName;
		std::ofstream ofs(filename + ".txt", std::ofstream::out);
		ofs << *gamePlayer[first];
		ofs.close();
	}
	
	return success;    
 }

 




 