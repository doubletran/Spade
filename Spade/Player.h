
#pragma once
#include "Card.h"
#include "Deck.h"
#include "Round.h"
struct Round;
enum Type { risky, moderate, safe };
class Player {

	int myNo;
	int finalScore;
	int bags;
	int teamNo;

	Type type;

	//EACH PLAYER HAS:
		//vector of hand containing value of their hand
	vector<Card>hand;
	Card curCard;
	vector<vector<int>>sorted;
	vector<int>avail = { 0,1,2,3 };
	vector<int>allow;
	vector<Card>handRanked;
public:

	Player(int playerNo);
	void newGame(vector<Card> newHand);
	void update();
	void setAllow(bool _spadeBreak);
	//function to order card to input value for each vectors
	void orderbySuit(vector<Card> unsorted);
	//bid value
	int bid;
	int bidSafe;
	int bidRisk;
	//mode = safe or risk
	int bidding(int mode);

	void goFirst(bool _spadeBreak);
	void askUserInput();
	//start function incase 
	void display();
	void setCurrentCard(int pos, Suit _suit);
	void playCard(Round &round);

	void chooseLargerCard(Card winCard);
	int roundWon;
	bool botMode;
	void calculateScore();

	void displayScore();
	int getSuit(bool _spadeBreak);
	vector<int> getValidSuits();

	void rank();
};
