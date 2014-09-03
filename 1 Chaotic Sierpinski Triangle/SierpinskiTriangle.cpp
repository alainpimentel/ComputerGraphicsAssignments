
#include <iostream>
#include <math.h>
#include <time.h>
#include <GL/glut.h>

// Holds a point
struct GLintPoint{
	GLint x, y;
};

// Draws the next dot on the screen
void drawDot(GLint x, GLint y) {
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

int random(int m) {
	return rand() % m;
}

// Displays the Sierpinski Triangle
void sierpinski_render() {
	glClear(GL_COLOR_BUFFER_BIT); // clear the screen
	GLintPoint T[3] = { { 10, 10 }, { 600, 100 }, { 300, 600 } }; // vertices of the triangle

	int index = rand() % 3; // choose the initial vertex randomly
	GLintPoint point = T[index];
	drawDot(point.x, point.y);

	for (int i = 0; i < 55000; i++) {
		index = random(3);
		point.x = (point.x + T[index].x) / 2;
		point.y = (point.y + T[index].y) / 2;
		drawDot(point.x, point.y);
	}
	glFlush();
}



void myKeyboard(unsigned char ch, int, int) {
	std::cout << "You pressed " << ch << std::endl;
}

void myMouse(int, int, int, int) {}

// Initializes various values
void myInit() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0f, 0.0f, 1.0f);
	glPointSize(2.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 800.0, 0.0, 600.0);
}

void stuff() {

}

int main(int argc, char** argv) {
	glutInit(&argc, argv);     // initialize the toolkit
	// set the display mode
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800, 600); // set window size
	// set window upper left corner position on screen
	glutInitWindowPosition(100, 150);
	// open the screen window (Title: my first attempt)
	glutCreateWindow("Sierpinski Assignment");
	// register the callback functions
	glutDisplayFunc(sierpinski_render);
	//glutMouseFunc(myMouse);
	//glutKeyboardFunc(myKeyboard);
	myInit(); // additional initializations as necessary
	glutMainLoop(); 	// go into a perpetual loop
}
