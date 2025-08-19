

#pragma once
#include "Player.h"


using namespace std;
struct Round {
	Card winCard;
	Suit winSuit;
	bool spadeBreakRound;
	int winner;
	//vector list contain card on order of playing for that round
	vector<Card>inCards;
	Round();
	Round( Card firstCard, int playerNo );

	//add function 
	//take Player obj as an argument
	void add(Card card_,int playerNo );
	void setWin(int playerNo, Card card);

	bool checkLarger(Card curCard);
};
