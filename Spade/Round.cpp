#include "Round.h"
#include <iostream>

using namespace std;
void display(int playerNo, Card currentCard);
Round::Round(Card firstCard, int playerNo) {
	spadeBreakRound = false;
	inCards.push_back(firstCard);
	setWin(playerNo, firstCard);
	display(playerNo, winCard);
}

void display(int playerNo, Card currentCard) {
	currentCard.display();
	cout << endl;
}

void Round::add(Card curCard, int playerNo) {
	display(playerNo, curCard);
	//if spade hasn't been broken, check if there'd be spadebreak
	if (!spadeBreakRound) {
		if ((this->winCard.suit != spades) && (curCard.suit == spades)) {
			//win immediately
			setWin(playerNo, curCard);
			spadeBreakRound = true;
		}
		else {
			if (checkLarger(curCard)) {
				setWin(playerNo, curCard);
			}
		}
	}
	else {
		setWin(playerNo, curCard);
	}
	inCards.push_back(curCard);
}

void Round::setWin(int playerNo, Card card) {
	this->winner = playerNo;
	this->winCard = card;
}
bool Round::checkLarger(Card currCard) {
	return ((currCard.suit == this->winCard.suit) && (currCard.number > this->winCard.number));
}

