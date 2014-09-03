#include <GL/glut.h>
#include <iostream>
#include <math.h>
#include <time.h>

// Holds a point
struct GLintPoint{
	GLint x, y;
};

// Draws the next dot on the screen
void drawDot(GLint x, GLint y) {
	glBegin(GL_POSITION);
	  glVertex2i(x, y);
	  glEnd();
}

void sierpinski_render() {
	glClear(GL_COLOR_BUFFER_BIT);
	GLintPoint T[3] = { { 10, 10 }, { 600, 100 }, { 300, 600 } };

	int index = rand() % 3;
	GLintPoint point = T[index];
	drawDot()
}

void myDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_LINE_LOOP);
	glVertex2i(100, 50);
	glVertex2i(100, 130);
	glVertex2i(150, 130);
	glEnd();
	glFlush();
}

void myKeyboard(unsigned char ch, int, int) {
	std::cout << "You pressed " << ch << std::endl;
}

void myMouse(int, int, int, int) {}

void myReshape(int, int) {}

void myInit() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0f, 1.0f, 0.0f);
	glPointSize(4.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);     // initialize the toolkit
	// set the display mode
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640, 480); // set window size
	// set window upper left corner position on screen
	glutInitWindowPosition(100, 150);
	// open the screen window (Title: my first attempt)
	glutCreateWindow("my first attempt");
	// register the callback functions
	glutDisplayFunc(myDisplay);
	glutReshapeFunc(myReshape);
	glutMouseFunc(myMouse);
	glutKeyboardFunc(myKeyboard);
	myInit(); // additional initializations as necessary
	glutMainLoop(); 	// go into a perpetual loop
}
