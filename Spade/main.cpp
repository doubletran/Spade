
#include <iostream>
#include <string.h>
#include <vector>
#include <cstdlib>
#include <time.h>
#include "Deck.h"
#include "Player.h"
#include "Round.h"
#include <iomanip>

using namespace std;



int main() {
	//call deck object to set up a full deck
	Deck deck;
	Player players[4] = { 0,1,2,3 };
	

	//call four hand object to set up four hands
	for (int i = 0; i < HAND; i++) {
		players[i].newGame(deck.hands[i]);
	}
	for (int i = 0; i < HAND; i++) {
		cout << "PLAYER " << i << endl;
		players[i].display();
		cout << endl;
	}

	
	//first player to start the game
	srand(time(0));
	int num = 0;
	cout << "Enter numbers of players: ";
	cin >> num;
	while (num > 4) {
		cout << "Value is out of range";
		cin >> num;
	}
	for (int i = 0; i < num; i++) {
		int userNo = rand() % HAND;
		players[userNo].botMode = false;
	}
	int posPlayer = 0;
	
	//THE GAME BEGINS........
	//each Round object will contain the current round including four cards 
	//played by each players
	bool spadeBreak = false;
	//loop over 13 rounds
	for (int r = 0; r < HAND_S; r++) {
		cout << "\n\nROUND  " << r + 1 << endl;
		//display the player's hand at the start of each game
		for (int i = 0; i < HAND; i++) {
			cout << "PLAYER " << i << endl;
			players[i].display();
			cout << endl;
		}
		cout << "Player " << posPlayer << " ";
		players[posPlayer].goFirst(spadeBreak);
		Round newRound( players[posPlayer].curCard, posPlayer);

		while (newRound.curRound.size() < HAND) {
			posPlayer++;
			if (!spadeBreak) {
				if (newRound.spadeBreakRound == true) {
					spadeBreak = true;
				}
			}
			if (posPlayer == HAND) {
				posPlayer = 0;
			}
			cout << "Player " << posPlayer << " ";
			players[posPlayer].playCard(newRound);
			newRound.add(players[posPlayer].curCard, players[posPlayer].myNo);
			
		}

		//end of round: update the player starting next round
		posPlayer = newRound.winner;
		cout << "\nWinner is player " << posPlayer<<endl;
		for (int i = 0; i < HAND; i++) {
			//if playerNo == final winner, wonRound increase by 1
			if (players[i].myNo == newRound.winner) { players[i].roundWon++; break; }
		}

	}

	//Display score
	cout << "\n\n-------SCORE-------";
	for (int i = 0; i < HAND; i++) {
		players[i].displayScore();
	}
	
}

