#include <gl/glut.h>
#include <iostream>
#include<math.h>
#include<time.h>
#include<gl/GL.h>


#define RED 2 
#define GREEN 3 
#define BLUE 4 
#define MAGENTA 5 
#define CYAN 6 
#define YELLOW 7 
#define BLACK 8 
#define ERASER 9
#define CIRCLE 10
#define PEN 11
#define HOLLOWCIRCLE 12
#define HOLLOWSQUARE 13
#define FILLEDSQUARE 14

int screenHeight = 600;
int brushSize = 3;
float red = 1.0;
float green = 0;
float blue = 1.0;
bool isShape = false;

int sx1;
int sx2;
int sy1;
int sy2;

using namespace std;
string shapeType = "";


void drawFilledSquare(double x1, double y1, double sidelength)
{
	double halfside = sidelength / 2;

	glColor3f(red, green, blue);
	glBegin(GL_POLYGON);

	glVertex2d(x1 + halfside, y1 + halfside);
	glVertex2d(x1 + halfside, y1 - halfside);
	glVertex2d(x1 - halfside, y1 - halfside);
	glVertex2d(x1 - halfside, y1 + halfside);

	glEnd();
	glFlush();
}

void drawHollowSquare(double x1, double y1, double sidelength)
{
	double halfside = sidelength / 2;

	glColor3f(red, green, blue);
	glBegin(GL_LINE_LOOP);

	glVertex2d(x1 + halfside, y1 + halfside);
	glVertex2d(x1 + halfside, y1 - halfside);
	glVertex2d(x1 - halfside, y1 - halfside);
	glVertex2d(x1 - halfside, y1 + halfside);

	glEnd();
	glFlush();
}

void drawCircle(int x, int y, double radius) {
	int i;
	int lineAmount = 100;
	double twicePi = 2.0f * 3.14;

	glBegin(GL_LINE_LOOP);
	for (i = 0; i <= lineAmount; i++) {
		glVertex2f(
			x + (radius * cos(i * twicePi / lineAmount)),
			y + (radius * sin(i * twicePi / lineAmount))
		);
	}
	glEnd();
	glFlush();

}

void drawHollowCircle(int x, int y, double radius) {
	float theta;
	glColor3f(red, green, blue);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++)
	{
		theta = i * 3.14 / 180;
		glVertex2f(x + radius * cos(theta), y + radius * sin(theta));
	}
	glEnd();
	glFlush();

}


void MyInit(void)
{
	glClearColor(1, 1, 1, 1);
	glColor3f(red, green, blue);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 800, 0, 600);
}

void MyDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}

void MoveMouseFunc(int button, int state, int mousex, int mousey)
{
	glColor3f(red, green, blue);
	if (!isShape)
	{
		GLint x = mousex;
		GLint y = screenHeight - mousey;
		glRecti(x, y, x + brushSize, y + brushSize);
		glRecti(x, y, x + brushSize, y + brushSize);
	}
	else
	{

		if (button == GLUT_LEFT_BUTTON
			&& state == GLUT_DOWN) {
			sx1 = mousex;
			sy1 = screenHeight - mousey;
		}
		else if (button == GLUT_LEFT_BUTTON
			&& state == GLUT_UP)
		{

			sx2 = mousex;
			sy2 = screenHeight - mousey;


			if (sx1 != 0 && sx2 != 0 && sy1 != 0 && sy2 != 0) {
				double r2;
				double xdif = abs(sx2 - sx1);
				double ydif = abs(sy2 - sy1);

				if (shapeType == "HOLLOWCIRCLE")
				{
					double r2 = pow(xdif, 2) + pow(ydif, 2);
					drawCircle(sx1, sy1, sqrt(r2));
				}
				else if (shapeType == "FILLEDCIRCLE")
				{
					double r2 = pow(xdif, 2) + pow(ydif, 2);

					drawHollowCircle(sx1, sy1, sqrt(r2));
				}
				else if (shapeType == "HOLLOWSQUARE")
				{

					drawHollowSquare(sx1, sy1, xdif * 2);
				}
				else if (shapeType == "FILLEDSQUARE")
				{

					drawFilledSquare(sx1, sy1, xdif * 2);
				}
			}
		}

	}



}


void MoveMouseFunc(int mousex, int mousey)
{
	screenHeight = glutGet(GLUT_WINDOW_HEIGHT);
	if (!isShape)
	{
		glColor3f(red, green, blue);
		GLint x = mousex;
		GLint y = screenHeight - mousey;
		glRecti(x, y, x + brushSize, y + brushSize);
		glRecti(x, y, x + brushSize, y + brushSize);

		glFlush();
	}
}

void MoveKeyboardFunc(unsigned char theKey, int mouseX, int mouseY)
{
	switch (theKey)
	{

	case '+':
		brushSize++;
		break;

	case '-':
		if (brushSize > 1.0)
		{
			brushSize--;
		}
		break;

	case 'c':
		glClear(GL_COLOR_BUFFER_BIT);
		glFlush();
		break;

	case 'e':
		exit(-1);
		break;

	default:
		break;
	}
}

void ProsesMenuEvents(int option)
{
	switch (option)
	{

	case RED:red = 1.0; green = 0.0; blue = 0.0; break;
	case GREEN:red = 0.0; green = 1.0; blue = 0.0; break;
	case BLUE:red = 0.0; green = 0.0; blue = 1.0; break;
	case MAGENTA:red = 1.0; green = 0.0; blue = 1.0; break;
	case CYAN:red = 0.0; green = 1.0; blue = 1.0; break;
	case YELLOW:red = 1.0; green = 1.0; blue = 0.0; break;
	case BLACK:red = 0.0; green = 0.0; blue = 0.0; break;
	case ERASER:red = 1.0; green = 1.0; blue = 1.0; isShape = false; break;
	case CIRCLE:isShape = true; shapeType = "FILLEDCIRCLE"; break;
	case HOLLOWCIRCLE:isShape = true; shapeType = "HOLLOWCIRCLE"; break;
	case HOLLOWSQUARE:isShape = true; shapeType = "HOLLOWSQUARE"; break;
	case FILLEDSQUARE:isShape = true; shapeType = "FILLEDSQUARE"; break;
	case PEN:isShape = false; break;

	default:

		break;
	}
}


void main()
{
	cout << "HELP :\n";
	cout << "You can see options when you right click \n";

	cout << "You can change brush size with +/- \n";
	cout << "You can clean screen with (c) \n";
	cout << "exit with (e)";


	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(200, 50);
	glutCreateWindow("Shahab Bahojb");
	glutDisplayFunc(MyDisplay);
	glutMotionFunc(MoveMouseFunc);
	glutMouseFunc(MoveMouseFunc);
	glutKeyboardFunc(MoveKeyboardFunc);
	glutCreateMenu(ProsesMenuEvents);
	glutAddMenuEntry("RED", RED);
	glutAddMenuEntry("GREEN", GREEN);
	glutAddMenuEntry("BLUE", BLUE);
	glutAddMenuEntry("MAGENTA", MAGENTA);
	glutAddMenuEntry("CYAN", CYAN);
	glutAddMenuEntry("YELLOW", YELLOW);
	glutAddMenuEntry("BLACK", BLACK);
	glutAddMenuEntry("ERASER", ERASER);
	glutAddMenuEntry("Filled CIRCLE", CIRCLE);
	glutAddMenuEntry("Hollow Circle", HOLLOWCIRCLE);
	glutAddMenuEntry("HollowSQUARE", HOLLOWSQUARE);
	glutAddMenuEntry("FILLEDSQUARE", FILLEDSQUARE);
	glutAddMenuEntry("PEN", PEN);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	MyInit();
	glutMainLoop();
}

