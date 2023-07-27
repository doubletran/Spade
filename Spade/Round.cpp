#include "Round.h"
#include <iostream>

using namespace std;
void display(int playerNo, Card currentCard);
Round::Round(Card firstCard, int playerNo) {
	spadeBreakRound = false;
	winCard = firstCard;
	suit = winCard.suit;
	curRound.push_back(winCard);
	winner = playerNo;
	display(playerNo, winCard);
}

void display(int playerNo, Card currentCard) {
	
	currentCard.display();
	cout << endl;
}

void Round::add(Card card_, int playerNo) {
	curCard = card_;
	display(playerNo, curCard);
	//update spade break round
	if (!spadeBreakRound) {
		if ((suit != spades) && (curCard.suit == spades)) {
			//win immediately
			winCard = curCard;
			winner = playerNo;
			spadeBreakRound = true;
		}
		else {
			findWinner(playerNo, curCard, winCard);
		}
	}
	else {
		findWinner(playerNo, curCard, winCard);
	}
	curRound.push_back(curCard);
}
void Round::findWinner(int playerNo, Card curCard, Card winCard) {
	if ((curCard.suit == winCard.suit) && (curCard.number > winCard.number)) {
		winner = playerNo;
		this->winCard = curCard;
	}
}


