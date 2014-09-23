//  Name: Alain Pimentel
#include <iostream>
#include <fstream>
#include <vector>
#include <GL/glut.h>
#include <math.h>

using namespace std;

// Custom Objects
struct Point
{
	float x;
	float y;
};

// Globals
const int LENGTH = 400;
const int WIDTH = 400;

vector<Point> points1;				// Save the original points
vector<Point> points2;				// Save the points to be morphed

float deltaT = 0.01f;			// Increment of tween
float tween = 0.0f;				// Initialize tween 
Point cp;						// Keep track of the current point

enum State
{
	Done,
	Tweening,
	Stopped
};
State state;					// Keep track of the drawing state

// Clears the screen
void clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

// Sets the Screensize and Background and foreground colors
void init()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0f, 0.0f, 0.0f);
	gluOrtho2D(0.0, 400.0, 0.0, 400.0);
}

// Draws a line between point a and point b
void lineTo(float x, float y)
{
	glBegin(GL_LINES);
	glVertex2f(cp.x, cp.y);
	glVertex2f(x, y);
	glEnd();
	glFlush();
	glColor3f(1.0f, 0.0f, 0.0f);
	cp = { x, y };
}

// change the current point
void moveTo(float x, float y)
{
	cp = { x, y };
}

// get both sets of points and store in vectors
void read_file_data()
{
	ifstream ifs("data.txt", ifstream::in);
	float s;
	int n = 0; int i = 0;
	vector<float> v1;
	vector<float> v2;
	for (i; ifs.good(); i++)
	{
		ifs >> s;
		if (i == 0)
			n = (int)s;
		if (i < n * 2 + 1 && i != 0)
		{
			v1.push_back(s);
		}
		else if (i != 0)
		{
			v2.push_back(s);
		}

	}
	ifs.close();

	for (unsigned i = 0; i<v1.size() - 1; i++)
	{
		if (!(i % 2))
		{
			Point tmp = { v1[i], v1[i + 1] };
			points1.push_back(tmp);
			tmp.x = v2[i]; tmp.y = v2[i + 1];
			points2.push_back(tmp);
		}
	}
}

// Tweening algorithm, returns intermiate point while tweening,  (or end)
Point tweenIt(Point point1, Point point2)
{
	float pointX = (1.0f - tween) * point1.x + tween * point2.x;
	float pointY = (1.0f - tween) * point1.y + tween * point2.y;
	return Point{ pointX, pointY };
}

// morphs every point into new point
void drawTween()
{
	for (unsigned i = 0; i < points1.size(); i++) {
		Point newPoint;
		newPoint = tweenIt(points1.at(i), points2.at(i));
		if (i == 0) moveTo(newPoint.x, newPoint.y);
		else lineTo(newPoint.x, newPoint.y);
	}
}

// calls drawtween and changes state to done when done
void displayFunc() 
{
	clear();
	if (state == Tweening) {
		clear();
		drawTween();
		glutSwapBuffers();
		if (tween >= 1.0 || tween <= 0.0) {
			state = Done;
		}
		glutPostRedisplay();
	}
}

// Increment the tween value
void changeTween()
{
	if (state != Stopped) // don't increment if the state is Stopped!
		tween += deltaT;
	if (tween > 1.0) {
		tween = 1.0f;
		//tween += deltaT;
	}
	else if (tween < 0) {
		tween = 0.0f;
	}
}

// Single mouse click listener
void myMouse(int button, int mouseState, int x, int y) {
	std::cout << "clicked mouse. STATE: " << state << std::endl;
	if (button == GLUT_LEFT_BUTTON && mouseState == GLUT_DOWN) { 
		if (state == Done) {
			// animation has finished, user restarts it bakcwards
			deltaT = -deltaT; // switch to backward or forward
			state = Tweening;
			glutPostRedisplay(); // start drawing again
		}
		else if (state == Tweening) {
			// user clicks the screen while tweening
			state = Stopped;
		}
		else if (state == Stopped) {
			// resume animation
			state = Tweening;
			glutPostRedisplay();
		}
	}
}


int main(int argc, char **argv)
{
	// Initialize Vectors points1, points2
	read_file_data();
	state = Tweening;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(LENGTH, WIDTH);
	//glutInitWindowPosition(0, 0);
	glutCreateWindow("Tweening");
	glutDisplayFunc(displayFunc);
	glutIdleFunc(changeTween); // increments the tween value
	glutMouseFunc(myMouse);
	glClearColor(1.0, 1.0, 1.0, 0.0);
	init();
	glutMainLoop();
}