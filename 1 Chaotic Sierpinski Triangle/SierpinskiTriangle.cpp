
#include <iostream>
#include <math.h>
#include <time.h>
#include <GL/glut.h>

const int screenHeight = 600;
const int screenWidth = 800;
int numberDots = 256;


// Holds a point
struct GLintPoint{
	GLint x, y;
};
GLintPoint corner[4];

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
void sierpinski_render(GLintPoint corner1, GLintPoint corner2, GLintPoint corner3, GLintPoint seed) {
	glClear(GL_COLOR_BUFFER_BIT); // clear the screen
	GLintPoint T[3] = { { corner1.x, corner1.y }, { corner2.x, corner2.y }, { corner3.x, corner3.y } }; // vertices of the triangle

	/*int index = rand() % 3; // choose the initial vertex randomly
	GLintPoint point = T[index];
	drawDot(point.x, point.y);
	*/
	for (int i = 0; i < numberDots; i++) {
		int index = random(3);
		GLint x = (seed.x + T[index].x) / 2;
		GLint y = (seed.y + T[index].y) / 2;
		drawDot(x, y);
		seed = { x, y };
	}
	glFlush();
}



void myKeyboard(unsigned char ch, int, int) {
	std::cout << "You pressed " << ch << std::endl;
	if (corner != NULL) {
		if (ch == 'U') {
			numberDots *= 2;
			if (numberDots > 1048756)
				numberDots = 1048756;
			sierpinski_render(corner[0], corner[1], corner[2], corner[4]);
		}
		else if (ch == 'D') {
			numberDots /= 2;
			if (numberDots < 256)
				numberDots = 256;
			sierpinski_render(corner[0], corner[1], corner[2], corner[4]);
		}
	}
}

void myMouse(int button, int state, int x, int y) {
	std::cout << "DOWNs\n";
	static int numCorners = 0;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		std::cout << "DOWN\n";
		corner[numCorners].x = x;
		corner[numCorners].y = screenHeight - y;
		if (++numCorners == 4) {
			sierpinski_render(corner[0], corner[1], corner[2], corner[4]);
			numCorners = 0;
		}
	}
	glFlush();
}

// Initializes various values
void myInit() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0f, 0.0f, 1.0f);
	glPointSize(2.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, screenWidth, 0.0, screenHeight);
}

void stuff() {

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
	glutDisplayFunc(stuff);
	glutMouseFunc(myMouse);
	glutKeyboardFunc(myKeyboard);
	myInit(); // additional initializations as necessary
	glutMainLoop(); 	// go into a perpetual loop
}
