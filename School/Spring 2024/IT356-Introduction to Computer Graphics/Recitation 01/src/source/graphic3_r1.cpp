#include<GL/glut.h>
#include<GL/gl.h>
#include<GL/glu.h>

void myRender() {
	//set display window's background color 
	glClearColor(0.0, 0.0, 0.0, 0.0);
	//clears our buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//perform any other matrix transformations here

	glBegin(GL_POLYGON);//start drawing diamond shape
		glColor3f(1.0f, 0.0f, 0.0f);//red color
		glVertex3f(0.0f, -0.75f, 0.0f);
		glColor3f(0.0f, 1.0f, 0.0f); //green color
		glVertex3f(-0.5f, 0.0f, 0.0f);
		glColor3f(0.0f, 1.0f, 1.0f); //cyan color
		glVertex3f(-0.333f, 0.25f, 0.0f);
		glVertex3f(0.333f, 0.25f, 0.0f);
		glColor3f(0.0f, 0.0f, 1.0f); //blue color
		glVertex3f(0.5f, 0.0f, 0.0f);
	glEnd();//end drawing of diamond

	glColor3f(0.0f, 0.0f, 0.0f);
	glLineWidth(5.0f);//set line width size to 10 pixels

	glBegin(GL_LINES); //starts drawing lines

		glVertex3f(-0.333f, 0.25f, 0.0f);
		glVertex3f(-0.167f, 0.0f, 0.0f);

		glVertex3f(-0.167f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.25f, 0.0f);

		glVertex3f(0.0f, 0.25f, 0.0f);
		glVertex3f(0.167f, 0.0f, 0.0f);

		glVertex3f(0.167f, 0.0f, 0.0f);
		glVertex3f(0.333f, 0.25f, 0.0f);

		glVertex3f(-0.167f, 0.0f, 0.0f);
		glVertex3f(0.0f, -0.75f, 0.0f);

		glVertex3f(0.167f, 0.0f, 0.0f);
		glVertex3f(0.0f, -0.75f, 0.0f);

		glVertex3f(0.5f, 0.0f, 0.0f);
		glVertex3f(-0.5f, 0.0f, 0.0f);

	glEnd();

	//ensures our objects are drawn right away
	glFlush();

	//if we are using double buffering
	glutSwapBuffers();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv); //process arguments

	//Initialize buffers
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);

	//Sets some initial stuff
	glutInitWindowPosition(400, 200);
	glutInitWindowSize(800, 600);

	//Creates window
	static int window = glutCreateWindow("Part II question III - Shane");

	//Display callback function, etc. myRender()
	glutDisplayFunc(myRender);

	//Enters main processing loop
	glutMainLoop();

	exit(0);
}