//  Name: Alain Pimentel
//  Assignment number: 1
//  Assignment: Sierpinski Triangle
//  File name: SierpinskiTriangle.cpp
//  Date last modified: September 8, 2014
//  Honor statement: I have neither given nor received any unauthorized help on this assignment. 
#include <iostream>
#include <math.h>
#include <time.h>
#include <GL/glut.h>

const int screenWidth = 1200;
const int screenHeight = 900;
int numberDots = 256;		// COntrols how many dots to draw for the triangle
static int numCorners = 0;	// Keeps track of how many corners have been inputted
bool dragging = false;		// flag to control the draggin state
int draggingPoint = -1;		// -1 means no point is being dragged. Use 0 - 2 depending on which point is being dragged

// a coordinate structure
struct GLintPoint{
	GLint x, y;
};
GLintPoint corner[4];		// Array to hold the triangle's points and seed

/**
Draws the next dot on the screen

@param x x-coordinate
@param y y-coordinate
*/
void drawDot(GLint x, GLint y) {
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

int random(int m) {
	return rand() % m;
}

/**
Displays the Sierpinski Triangle

@param corner1, corner2, corner 3 The three points to form a triangle
@param seed A point to be used as a seed to generate the triangle
*/
void sierpinskiRender(GLintPoint corner1, GLintPoint corner2, GLintPoint corner3, GLintPoint seed) {
	glClear(GL_COLOR_BUFFER_BIT); // clear the screen
	GLintPoint T[3] = { { corner1.x, corner1.y }, { corner2.x, corner2.y }, { corner3.x, corner3.y } }; // vertices of the triangle

	for (int i = 0; i < numberDots; i++) {
		int index = random(3);
		GLint x = (seed.x + T[index].x) / 2; // generate midpoint between randomly chosen vertice and seed
		GLint y = (seed.y + T[index].y) / 2;
		drawDot(x, y);
		seed = { x, y }; // the seed becomes the midpoint
	}
	glFlush(); // draw the new triangle
}


// Keyboard listener
void myKeyboard(unsigned char ch, int, int) {
	if (corner != NULL) {
		if (ch == 'U') { // Double the number of dots up to 1048756
			numberDots *= 2;
			if (numberDots > 1048756)
				numberDots = 1048756;
			sierpinskiRender(corner[0], corner[1], corner[2], corner[3]);
		}
		else if (ch == 'D') { // Divide the number of dots by 2 up to 256
			numberDots /= 2;
			if (numberDots < 256)
				numberDots = 256;
			sierpinskiRender(corner[0], corner[1], corner[2], corner[3]);
		}
		else if (ch == 'C') { // Clear the screen, reset the number of corners
			numCorners = 0;
			glClear(GL_COLOR_BUFFER_BIT); 
			glFlush();
		}
	}
}

// Single mouse click listener
void myMouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) { // Controls single clicks to draw the triangle
		corner[numCorners].x = x;
		corner[numCorners].y = screenHeight - y;
		if (++numCorners == 4) { // if four clicks were saved, draw triangle
			sierpinskiRender(corner[0], corner[1], corner[2], corner[3]);
		}
	}
	else if (dragging && button == GLUT_LEFT_BUTTON && state == GLUT_UP) { // Controls when the user lets go of the left click 
		if (draggingPoint > -1 && numCorners > 4) {
			dragging = false; // user can drag a new point
			draggingPoint = -1;
		}
	}
}

// Dragging motion
void myMovedMouse(int x, int y) {
	std::cout << draggingPoint << std::endl;
	if (corner != NULL && !dragging && numCorners > 4) { // if the user is already draggin, dont do anything
		int stdX = 10; // add a bigger area to make it easier to drag a point
		int stdY = 10;
		// Check the selected point is within the desired area, if it change the necessary variables to draw the new triangle when the user lets go of the click
		if ((corner[0].x - stdX <= x && x <= corner[0].x + stdX) && (corner[0].y - stdY <= screenHeight - y && screenHeight - y <= corner[0].y + stdY)) {
			if (draggingPoint < 0)
				draggingPoint = 0;
			dragging = true;
		}
		else if ((corner[1].x - stdX <= x && x <= corner[1].x + stdX) && (corner[1].y - stdY <= screenHeight - y && screenHeight - y <= corner[1].y + stdY)) {
			if (draggingPoint < 0)
				draggingPoint = 1;
			dragging = true;
		}
		else if ((corner[2].x - stdX <= x && x <= corner[2].x + stdX) && (corner[2].y - stdY <= screenHeight - y && screenHeight - y <= corner[2].y + stdY)) {
			if (draggingPoint < 0)
				draggingPoint = 2;
			dragging = true;
		}
		else if ((corner[3].x - stdX <= x && x <= corner[3].x + stdX) && (corner[3].y - stdY <= screenHeight - y && screenHeight - y <= corner[3].y + stdY)) {
			if (draggingPoint < 0)
				draggingPoint = 3;
			dragging = true;
		}
	}
	else if (draggingPoint > -1 && numCorners > 4) { // Only drag when all points have been inputted
		GLintPoint newPoint = { x, screenHeight - y }; // point to be moved
		if (draggingPoint == 0)
			corner[0] = newPoint;
		else if (draggingPoint == 1)
			corner[1] = newPoint;
		else if (draggingPoint == 2)
			corner[2] = newPoint;
		else if (draggingPoint == 3)
			corner[3] = newPoint;

		sierpinskiRender(corner[0], corner[1], corner[2], corner[3]); // redraw triangle with the new point
	}
}

// Initializes the screen
void myInit() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0f, 0.0f, 1.0f);
	glPointSize(2.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, screenWidth, 0.0, screenHeight);
}

void displayFunc() {
	glClear(GL_COLOR_BUFFER_BIT); // clear the screen
	glFlush();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);     // initialize the toolkit
	// set the display mode
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(screenWidth, screenHeight); // set window size
	// set window upper left corner position on screen
	glutInitWindowPosition(100, 150);
	// open the screen window (Title: my first attempt)
	glutCreateWindow("Sierpinski Assignment");
	// register the callback functions
	glutDisplayFunc(displayFunc);
	glutMouseFunc(myMouse);
	glutMotionFunc(myMovedMouse);
	glutKeyboardFunc(myKeyboard);
	myInit(); // additional initializations as necessary
	glutMainLoop(); 	// go into a perpetual loop
}
