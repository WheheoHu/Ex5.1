#include <stdlib.h>
#include "glut.h"
#include "Sphere.h"

float lineColor[] = { 0.2f, 0.2f, 0.2f, 1 };

static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;
Sphere sp_1(30, 15, 10);
Sphere sp_2(30, 15, 10);

void ChangeSize(int w, int h);
void SpecialKeys(int key, int x, int y);
void RenderScene(void);
void SetupRC();

int main() {
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Ambient Light");
	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(SpecialKeys);
	glutDisplayFunc(RenderScene);

	SetupRC();
	glutMainLoop();

	return 0;
}

void ChangeSize(int w, int h)
{
	GLfloat nRange = 80.0f;
	// Prevent a divide by zero
	if (h == 0)
		h = 1;

	// Set Viewport to window dimensions
	glViewport(0, 0, w, h);

	// Reset coordinate system
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Establish clipping volume (left, right, bottom, top, near, far)
	if (w <= h)
		glOrtho(-nRange, nRange, -nRange * h / w, nRange*h / w, -nRange, nRange);
	else
		glOrtho(-nRange * w / h, nRange*w / h, -nRange, nRange, -nRange, nRange);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void SpecialKeys(int key, int x, int y)
{
	if (key == GLUT_KEY_UP)
		xRot -= 5.0f;

	if (key == GLUT_KEY_DOWN)
		xRot += 5.0f;

	if (key == GLUT_KEY_LEFT)
		yRot -= 5.0f;

	if (key == GLUT_KEY_RIGHT)
		yRot += 5.0f;

	if (key > 356.0f)
		xRot = 0.0f;

	if (key < -1.0f)
		xRot = 355.0f;

	if (key > 356.0f)
		yRot = 0.0f;

	if (key < -1.0f)
		yRot = 355.0f;

	// Refresh the Window
	glutPostRedisplay();
}

void RenderScene(void)
{
	// Clear the window with current clearing color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Save the matrix state
	glPushMatrix();
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);
	glViewport(0, 0, 400, 400);
	glColor3f(1, 0, 0);
	sp_1.printSelf();
	sp_1.drawWithLines(lineColor);

	glViewport(400, 0, 400, 400);
	glColor3f(1, 1, 0);
	sp_2.printSelf();
	sp_2.drawWithLines(lineColor);

	glViewport(0, 400, 400, 400);
	GLUquadricObj *quadObj = gluNewQuadric();
	gluCylinder(quadObj,30,30,40,20,20);

	glViewport(400, 400, 400, 400);
	glColor3f(0, 0, 1);
	glutSolidCone(30, 40, 20, 10);
	// Display the results
	glutSwapBuffers();
}

void SetupRC()
{
	GLfloat ambientLight[] = { 0.4f, 0.4f, 0.4f, 1.0f };
	GLfloat diffuseLight[] = { 0.7f, 0.7f, 0.7f, 1.0f };

	glEnable(GL_DEPTH_TEST); // Hidden surface removal
	glEnable(GL_CULL_FACE);	// Do not calculate inside of jet
	glFrontFace(GL_CCW);		 // Counter clock-wise polygons face out

	// Lighting stuff
	glEnable(GL_LIGHTING); // Enable lighting

	// Set light model to use ambient light specified by ambientLight
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glEnable(GL_LIGHT0);


	glEnable(GL_COLOR_MATERIAL); // Enable Material color tracking

	// Front material ambient and diffuse colors track glColor
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	// Nice light blue
	glClearColor(0, 0, 0, 1.0f);
}


//I try this in anydesk 
//It's Awesome!!!