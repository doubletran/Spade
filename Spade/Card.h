#pragma once
/*Card.h
* variable: number and suit for each card*/
/// Class Card contains number and suits of each card in the deck

//from 2 to to are integers withou names
const int JACK = 11;
const int QUEEN = 12;
const int KING = 13;
const int ACE = 14;

//enum type for four decks
enum Suit { hearts, diamonds, clubs, spades };

struct Card {
	int number;
	Suit suit;


	Card();
	Card(int _number, Suit _suit);
	void display();
};
