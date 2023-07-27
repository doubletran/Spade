
#pragma once
#include<string.h>
#include<vector>
#include <cstdlib>
#include<time.h>
#include "Card.h"
using namespace std;

//initial setup and distribute card
const int SIZE = 52;
const int HAND = 4;
const int HAND_S = 13;

struct Deck {
	Card deck[SIZE];

	vector<vector<Card>> hands;
	Deck();
	//create an order deck
	void order();
	//distribute card by four hand
	void setHand();
};

