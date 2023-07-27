
#include "Player.h"
#include <iostream>
#include <time.h>
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>
using namespace std;

const int safeR = 3;
const int riskR = 4;
//prototype
int bidOnSuit(vector<int>value, int mode);

//constructor
Player::Player(int playerNo) {
	myNo = playerNo;
	finalScore = 0;
	bidSafe = 0, bidRisk = 0, bid = 0;
	roundWon = 0;
	botMode = true;
	teamNo = myNo > 1 ? myNo - 2 : myNo + 2;
	type = static_cast<Type>(rand() % 3);

}//constructor
void Player::newGame(vector<Card> hand) {
	roundWon = 0;
	bags = 0;
	orderbySuit(hand);
	update();


	bidSafe = bidding(safeR);
	bidRisk = bidding(riskR);
	bid = (bidSafe + bidRisk) / 2;
}
//put in order by suit
//put the value of card in the array of their suit
void Player::orderbySuit(vector<Card>unsorted) {
	//initialize 2d vector hand 
	for (int i = 0; i < HAND; i++) {
		vector<int>h;
		sorted.push_back(h);
	}
	for (int i = 0; i < unsorted.size(); i++) {
		int suitValue = unsorted[i].suit;
		sorted[suitValue].push_back(unsorted[i].number);
	}
}

//bidding function return variable bit value 
int Player::bidding(int mode) {
	/*bid on spade
	If the number of spade card exceed the difference of other suit card, each extra spade card is counted as a bid*/
	int _bid = 0;
	for (int i = 0; i < 3; i++) {
		_bid += (sorted[3].size() - _bid) > (mode - sorted[i].size()) ? mode - sorted[i].size() : _bid;
	}
	for (int i = 0; i < 4; i++) {
		_bid += bidOnSuit(sorted[i], mode);
	}
	return _bid;
}
//funtion to return bids depending on each suit's power
int bidOnSuit(vector<int>value, int mode) {
	int MAX = 14;
	int _bid = mode - value.size();
	for (const int& i : value) {
		while (i == MAX) { _bid++;	MAX--; }
	}
	return _bid;
}
//update vector of availability of current cards for each suit
void Player::update() {
	for (int i = 0; i < avail.size(); i++) {
		if (sorted[avail[i]].size() == 0) {
			avail.erase(avail.begin() + i);
		}
	}
	allow = avail;


}

/*setCurrentCard
* set the current card following the parameters
* delete the current card from the player hand
*/

void Player::setCurrentCard(int pos, Suit _suit) {
	curCard = { sorted[_suit][pos], _suit };
	sorted[_suit].erase(sorted[_suit].begin() + pos);
	update();

}



//display bid
void Player::display() {
	for (int i = 0; i < HAND; i++) {
		for (int j = 0; j < sorted[i].size(); j++) {
			Card card(sorted[i][j], static_cast<Suit>(i));
			card.display();
		}
	}

	cout << "Bid: " << bid << endl;
}
void Player::goFirst(bool _spadeBreak) {
	if ((!_spadeBreak) && (allow[allow.size() - 1] == 3)) {
		allow.pop_back();
	}

	if (botMode) {
		Card temp(0, static_cast<Suit>(allow[rand() % allow.size()]));
		chooseCard(temp);
	}
	else {
		askUserInput();
	}
}
void Player::askUserInput(){
	int index = 0;
	int limit = 1;
	for (int suit : allow) {
		for (int pos : sorted[suit]) {
			cout << limit++ << ": ";
			Card _card(pos, static_cast<Suit>(suit));
			_card.display();
			cout << "  ";
		}
	}
	cout << "\nPlease enter your choice of card:  ";
	cin >> index;
	while ((index == 0) || (index > limit)) {
		cin >> index;
		cout << "Invalid input. Please try again: ";
	}
	int count = 1;
	while (count <= index) {
		for (int suit : allow) {
			for (int pos = 0; pos < sorted[suit].size(); pos++) {
				if (index == count) {
					setCurrentCard(pos, static_cast<Suit>(suit));
				}
				count++;
			}
		}
	}
	
}

void Player::playCard(Round &round) {
	if (sorted[round.suit].size() > 0) {
		allow.clear();
		allow.push_back(round.suit);
	}
	Suit _curSuit = static_cast<Suit>(allow[rand() % allow.size()]);
	Card winCard = round.winCard;
	if (botMode) {
		if (winCard.suit == _curSuit) {
			chooseCard(winCard);
		}
		else {
			if (sorted[spades].size()>0) {
				//create Card object with the smallest number
				Card temp(0, spades);
				chooseCard(temp);
			}
			else {
				Card temp(0, _curSuit);
				chooseCard(temp);
			}
		}
	}
	else {
		askUserInput();
	}
}
void Player::chooseCard(Card winCard) {
	Suit _suit = winCard.suit;
	for (int i = 0; i < sorted[_suit].size(); i++) {
		if (sorted[_suit][i] > winCard.number) {
			setCurrentCard(i, _suit);
			break;
		}
		else {
			setCurrentCard(sorted[_suit].size() - 1, _suit);
			break;
		}
	}
}
void Player::calculateScore() {
	//if bid is met
	if (roundWon >= bid) {
		bags += roundWon - bid;
		finalScore += bid * 10 + (roundWon - bid);
	}
	else {
		finalScore -= bid * 10;
	}
	if (bags >= 10) {
		finalScore -= 100;
		bags = 0;
	}
}
void Player::displayScore() {
	calculateScore();
	cout << "\nPlayer " << myNo
		<< "\tBids  " << bid
		<<"\t\tWin  "<<roundWon
		<< "\t\tBags  " << bags
		<< "\t\tScore  " << finalScore;

}
int percentWin(vector<int>suitArray, int value) {
	const int MAX_VAL = 14;
	const int MAX_SCORE = 51;
	int score = 0;
	for (int i = 0; i < suitArray.size(); i++) {
		if (value == suitArray[i]) {
			score = MAX_VAL - suitArray[i] - (i + 1);
			break;
		}
		
	}
	return score;

}


void Player::rank() {
	const int  MAX_VAL = 14;
	const int MAX_SCORE = 51;
	int value = MAX_VAL;
	int score = MAX_SCORE;
	vector<vector<int>>scoreList;
	for (int i = 0; i < HAND; i++) {
		vector<int>scoreSuit;
		scoreList.push_back(scoreSuit);
	}
	for (int val : sorted[spades]) {
		int score = MAX_VAL - val;
		for (int val2 : sorted[spades]) {
			//if we have larger card
			if (val2 > val) {
				score--;
			}
			else if (val2 == val) {
				break;
			}
		}
		scoreList[HAND - 1].push_back(score);
	}
	for (int i = 0; i < 3; i++) {
		int size = 0;
		for (int val : sorted[i]) {
			size++;
			int score = MAX_VAL - val +size;
			int tracker = 0;
			while (sorted[i][tracker++] > val) {
				score--;
			}
			scoreList[i].push_back(score);
		}
	}
	for (vector<int> scoreSuit : scoreList) {
		cout << endl;
		for (int i : scoreSuit) {

			cout << i<< " ";
		}
	}

}


