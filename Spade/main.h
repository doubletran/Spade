

//include this first
#ifdef WIN32
#include <windows.h>
#pragma warning(disable:4996)
#endif
#include <iostream>
#include <string.h>
#include <vector>
#include <cstdlib>
#include <time.h>
#include "Deck.h"
#include "Player.h"
#include "Round.h"
#include <iomanip>
#include "glew.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <glut.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

const char* WINDOWTITLE = "OpenGL / GLUT Sample -- Joe Graphics";
const char* GLUITITLE = "SPADE";
const int INIT_WINDOW_SIZE = 600;
// active mouse buttons (or them together):

const int LEFT = 4;
const int MIDDLE = 2;
const int RIGHT = 1;
const GLfloat BACKCOLOR[] = { 0., 0., 0., 1. };
int		MainWindow;
int		Xmouse, Ymouse;			// mouse values
float	Time;
int		ActiveButton;
GLuint CardTex;
GLuint CardDL;

// initialize the glut and OpenGL libraries:
//	also setup callback functions
void	InitLists();
void	InitMenus();
void	Keyboard(unsigned char, int, int);
void	MouseButton(int, int, int, int);
void	MouseMotion(int, int);
void	Reset();
void	Resize(int, int);
void	Visibility(int);
void	InitTextures();
void InitLists() {
	const double CARD_HEIGHT = 2.f;
	const double CARD_WIDTH = 1.5f;
	CardDL = glGenLists(1);
	glNewList(CardDL, GL_COMPILE);
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, CardTex);
	glBegin(GL_QUADS);
	// Top-left

// Bottom-left corner
	glTexCoord2d(0.0, 0.0); // Texture coordinate
	glVertex3f(0.0f,0.0f, 0.0f); // Vertex position

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
void InitTextures() {
	glGenTextures(1, &CardTex);
	glBindTexture(GL_TEXTURE_2D, CardTex);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	int width, height, nrChannels;
	unsigned char* data = stbi_load("../Spade/asset/Cards/card_clubs_1.png", &width, &height, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		
	}
	else {
		cout << "Failed to load texture" << endl;
	}
	stbi_image_free(data);


}
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
	glCallList(CardDL);
	glFlush();

}


void
Animate()
{
	// put animation stuff in here -- change some global variables for Display( ) to find:
	const int MS_PER_CYCLE = 10000;		// 10000 milliseconds = 10 seconds
	int ms = glutGet(GLUT_ELAPSED_TIME);
	ms %= MS_PER_CYCLE;							// makes the value of ms between 0 and MS_PER_CYCLE-1
	Time = (float)ms / (float)MS_PER_CYCLE;		// makes the value of Time between 0. and slightly less than 1.

	// for example, if you wanted to spin an object in Display( ), you might call: glRotatef( 360.f*Time,   0., 1., 0. );

	// force a call to Display( ) next time it is convenient:


	glutSetWindow(MainWindow);
	glutPostRedisplay();
}
void
InitGraphics()
{



	// set the initial window configuration:

	glutInitWindowPosition(0, 0);
	glutInitWindowSize(INIT_WINDOW_SIZE, INIT_WINDOW_SIZE);

	// open the window and set its title:

	MainWindow = glutCreateWindow(WINDOWTITLE);
	glutSetWindowTitle(WINDOWTITLE);

	// set the framebuffer clear values:

	glClearColor(BACKCOLOR[0], BACKCOLOR[1], BACKCOLOR[2], BACKCOLOR[3]);

	// setup the callback functions:
	// DisplayFunc -- redraw the window
	// ReshapeFunc -- handle the user resizing the window
	// KeyboardFunc -- handle a keyboard input
	// MouseFunc -- handle the mouse button going down or up
	// MotionFunc -- handle the mouse moving with a button down
	// PassiveMotionFunc -- handle the mouse moving with a button up
	// VisibilityFunc -- handle a change in window visibility
	// EntryFunc	-- handle the cursor entering or leaving the window
	// SpecialFunc -- handle special keys on the keyboard
	// SpaceballMotionFunc -- handle spaceball translation
	// SpaceballRotateFunc -- handle spaceball rotation
	// SpaceballButtonFunc -- handle spaceball button hits
	// ButtonBoxFunc -- handle button box hits
	// DialsFunc -- handle dial rotations
	// TabletMotionFunc -- handle digitizing tablet motion
	// TabletButtonFunc -- handle digitizing tablet button hits
	// MenuStateFunc -- declare when a pop-up menu is in use
	// TimerFunc -- trigger something to happen a certain time from now
	// IdleFunc -- what to do when nothing else is going on

	glutSetWindow(MainWindow);
	glutDisplayFunc(Display);
	//glutReshapeFunc(Resize);
	//glutKeyboardFunc(Keyboard);
	glutMouseFunc(MouseButton);
	//glutMotionFunc(MouseMotion);
	//glutPassiveMotionFunc(MouseMotion);
	//glutPassiveMotionFunc( NULL );
	glutEntryFunc(NULL);
	glutSpecialFunc(NULL);
	glutSpaceballMotionFunc(NULL);
	glutSpaceballRotateFunc(NULL);
	glutSpaceballButtonFunc(NULL);
	glutButtonBoxFunc(NULL);
	glutDialsFunc(NULL);
	glutTabletMotionFunc(NULL);
	glutTabletButtonFunc(NULL);
	glutMenuStateFunc(NULL);
	glutTimerFunc(-1, NULL, 0);

	// setup glut to call Animate( ) every time it has
	// 	nothing it needs to respond to (which is most of the time)
	// we don't need to do this for this program, and really should set the argument to NULL
	// but, this sets us up nicely for doing animation

	glutIdleFunc(Animate);

	// init the glew package (a window must be open to do this):

#ifdef WIN32
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		fprintf(stderr, "glewInit Error\n");
	}
	else
		fprintf(stderr, "GLEW initialized OK\n");
	fprintf(stderr, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
#endif

	// all other setups go here, such as GLSLProgram and KeyTime setups:
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 10.0, 0.0, 10.0);
	glMatrixMode(GL_MODELVIEW);

}


// called when the mouse button transitions down or up:

void
MouseButton(int button, int state, int x, int y)
{
	int b = 0;			// LEFT, MIDDLE, or RIGHT



	// get the proper button bit mask:

	switch (button)
	{
	case GLUT_LEFT_BUTTON:
		b = LEFT;		break;

	case GLUT_MIDDLE_BUTTON:
		b = MIDDLE;		break;

	case GLUT_RIGHT_BUTTON:
		b = RIGHT;		break;


	default:
		b = 0;
		fprintf(stderr, "Unknown mouse button: %d\n", button);
	}

	// button down sets the bit, up clears the bit:

	if (state == GLUT_DOWN)
	{
		Xmouse = x;
		Ymouse = y;
		ActiveButton |= b;		// set the proper bit
	}
	else
	{
		ActiveButton &= ~b;		// clear the proper bit
	}

	glutSetWindow(MainWindow);
	glutPostRedisplay();

}
