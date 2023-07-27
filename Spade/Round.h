

#pragma once
#include "Player.h"


using namespace std;
struct Round {
	Card curCard;
	Card winCard;
	Suit suit;
	Suit winSuit;
	Round();

	Round( Card firstCard, int playerNo );

	//vector list contain card on order of playing for that round
	vector<Card>curRound;
	//add function 
	//take Player obj as an argument
	void add(Card card_,int playerNo );

	void findWinner(int playerNo, Card curCard, Card winCard);
	bool spadeBreakRound;
	int winner;
	bool spadeBreak;
	

};
