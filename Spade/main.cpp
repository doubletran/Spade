
#include "main.h"

using namespace std;
int userNo = rand() % HAND;
//LEFT, TOP, RIGHT, BOTTOM position
enum Position {LEFT, TOP, RIGHT, BOTTOM};
int topPlayerNo, leftPlayerNo, rightPlayerNo, bottomPlayerNo;
void
Display()
{

	// set which window we want to do the graphics into:
	glutSetWindow(MainWindow);

	glClear(GL_COLOR_BUFFER_BIT);

	glDisable(GL_DEPTH_TEST);

	// set the viewport to be a square centered in the window:

	GLsizei vx = glutGet(GLUT_WINDOW_WIDTH);
	GLsizei vy = glutGet(GLUT_WINDOW_HEIGHT);
	GLsizei v = vx < vy ? vx : vy;			// minimum dimension
	GLint xl = (vx - v) / 2;
	GLint yb = (vy - v) / 2;
	glViewport(xl, yb, v, v);

	glEnable(GL_TEXTURE_2D);
	//glCallList(CardDL);
	//LEFT
	for (int i = 0; i < HAND; i++) {
		glTranslatef(1.f, 0.f, 0.f);
		glRotatef(90, 0, 0, 1);
		players[i].display();
		glRotatef(-90, 0, 0, 1);
		glTranslatef(-1.f, 0.f, 0.f);
	}
	glPushMatrix();
	glTranslatef(0, 9, 0);
	//cout << "PLAYER " << i << endl;
	players[topPlayerNo].display();
	//glTranslatef(0, -9, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.f, 0.f, 0.f);
	glRotatef(90, 0, 0, 1);
	players[leftPlayerNo].display();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(10.f, 0.f, 0.f);
	glRotatef(90, 0, 0, 1);
	players[rightPlayerNo].display();
	glPopMatrix();

	players[bottomPlayerNo].display();
	glFlush();

}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);

	InitGraphics();
	Card::InitTexture3d();
	Position firstPlayerPos = static_cast<Position>(rand() % HAND);
	for (int i = 0; i < HAND; i++) {
		Position pos = static_cast<Position>(i + firstPlayerPos);
		switch (pos) {
		case TOP:
			topPlayerNo = i;
			break;
		case LEFT:
			leftPlayerNo = i;
			break;
		case RIGHT:
			rightPlayerNo = i;
			break;
		case BOTTOM:
			bottomPlayerNo = i;
			break;
		}
	}
	//InitTextures();
	//InitLists();
	//call four hand object to set up four hands

	players[userNo].botMode = false;

	for (int i = 0; i < HAND; i++) {
		players[i].newGame(deck.hands[i]);
	}

	glutSetWindow(MainWindow);
	glutMainLoop();
	/*
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
	*/
	return 0;
}


