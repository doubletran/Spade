
//Card.cpp
#include "Card.h"
#include <iostream>
using namespace std;

Card::Card() :number(0), suit() {};
Card::Card(int _number, Suit _suit) : number(_number), suit(_suit) {};

void Card::display() {
	if (number >= 2 && number <= 10) cout << number;
	else
		switch (number) {
		case JACK: cout << "J"; break;
		case QUEEN: cout << "Q"; break;
		case KING: cout << "K"; break;
		case ACE: cout << "A"; break;
		}
	switch (suit) {
	case hearts: cout << static_cast<char>(3); break;
	case diamonds: cout << static_cast<char> (4); break;
	case clubs: cout << static_cast<char>(5); break;
	case spades: cout << static_cast<char>(6); break;
	}
	cout << ' ';
}
