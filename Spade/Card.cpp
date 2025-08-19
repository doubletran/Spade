
//Card.cpp
#include "Card.h"
#include <iostream>
using namespace std;

Card::Card() :number(0), suit() {};
Card::Card(int _number, Suit _suit) : number(_number), suit(_suit) {};
const double CARD_HEIGHT = 2.f;
const double CARD_WIDTH = 1.5f;
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
void Card::InitTexture() {
	string suitName;
	switch (suit) {
	case hearts:
		suitName = "heart";
		break;
	case diamonds:
		suitName = "diamond";
		break;
	case clubs:
		suitName = "clubs";
		break;
	case spades:
		suitName = "spade";
		break;
	}
	string number_string = to_string(number);
	if (number == ACE) {
		number_string = "1";
	}
	string cardTexName = "../Spade/asset/Cards/card_" + suitName + "_" + number_string + ".png";
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	int width, height, nrChannels;
	unsigned char* data = stbi_load(cardTexName.c_str(), &width, &height, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}
	else {
		cout << "Failed to load texture "  +  cardTexName << endl;
	}
	stbi_image_free(data);
}

void Card::InitList(const int pos) {
	InitTexture();


	list_pos = pos;
	dlist = pos;
	glNewList(dlist, GL_COMPILE);
	glEnable(GL_TEXTURE_2D);
	
	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_QUADS);
	// Top-left

// Bottom-left corner
	glTexCoord2d(0.0, 0.0); // Texture coordinate
	glVertex3f(0.0f, 0.0f, 0.0f); // Vertex position

	// Bottom-right corner
	glTexCoord2d(1.0, 0.0); // Texture coordinate
	glVertex3f(CARD_WIDTH, 0.f, 0.0f); // Vertex position

	// Top-right corner
	glTexCoord2d(1.0, 1.0); // Texture coordinate
	glVertex3f(CARD_WIDTH, CARD_HEIGHT, 0.0f); // Vertex position

	// Top-left corner
	glTexCoord2d(0.0, 1.0); // Texture coordinate
	glVertex3f(0.f, CARD_HEIGHT, 0.0f); // Vertex position
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glEndList();
}
void Card::DisplayList() {
	InitTexture();

	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_QUADS);
	// Top-left

// Bottom-left corner
	glTexCoord2d(0.0, 0.0); // Texture coordinate
	glVertex3f(0.0f, 0.0f, 0.0f); // Vertex position

	// Bottom-right corner
	glTexCoord2d(1.0, 0.0); // Texture coordinate
	glVertex3f(CARD_WIDTH, 0.f, 0.0f); // Vertex position

	// Top-right corner
	glTexCoord2d(1.0, 1.0); // Texture coordinate
	glVertex3f(CARD_WIDTH, CARD_HEIGHT, 0.0f); // Vertex position

	// Top-left corner
	glTexCoord2d(0.0, 1.0); // Texture coordinate
	glVertex3f(0.f, CARD_HEIGHT, 0.0f); // Vertex position
	glEnd();
	glDisable(GL_TEXTURE_2D);

}