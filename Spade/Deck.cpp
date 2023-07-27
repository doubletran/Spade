
#include "Deck.h"

Deck::Deck() {
	order();
	setHand();
}
//Function order() to initiate an ordered card
void Deck::order() {
	int pos = 0;
	for (int i = 0; i < 4; i++) {
		for (int n = 14; n >= 2; n--) {
			Card temp(n, static_cast<Suit>(i));
			deck[pos] = temp;
			++pos;
		}
	}
}

void Deck::setHand() {
	//seed time randmly
	srand(time(NULL));
	//initialize 2d vector hand 
	for (int i = 0; i < HAND; i++) {
		vector<Card>h;
		hands.push_back(h);
	}

	//tracking list to keep track of full vectors
	vector<int>list = { 0,1,2,3 };
	for (int i = 0; i < SIZE; i++) {
		int h = rand() % list.size();
		int pos = list[h];

		//add card to each hand governed randomly
		hands[pos].push_back(deck[i]);

		// if hand's size reach 13, erase vector's index from the list
		if (hands[pos].size() == 13) {
			list.erase(list.begin() + h);
		}
	}
}

