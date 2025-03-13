#include<GL/glut.h>
#include<GL/gl.h>
#include<GL/glu.h>

void MyRender()
{
	//clear color and depth buffer 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();//load identity matrix

	glLineWidth(2.0f);//set line width to 25 pixels
	
	glColor3f(0.0f, 1.0f, 1.0f);//cyan color
	
	glBegin(GL_LINES); //starts drawing lines
		glVertex3f(-0.5f, 0.0f, 0.0f);
		glVertex3f(-0.375f, 0.25f, 0.0f);

		glVertex3f(-0.375f, 0.25f, 0.0f);
		glVertex3f(-0.25f, 0.0f, 0.0f);

		glVertex3f(-0.25f, 0.0f, 0.0f);
		glVertex3f(-0.125f, 0.25f, 0.0f);

		glVertex3f(-0.125f, 0.25f, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);

		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.125f, 0.25f, 0.0f);

		glVertex3f(0.125f, 0.25f, 0.0f);
		glVertex3f(0.25f, 0.0f, 0.0f);

		glVertex3f(0.25f, 0.0f, 0.0f);
		glVertex3f(0.375f, 0.25f, 0.0f);

		glVertex3f(0.375f, 0.25f, 0.0f);
		glVertex3f(0.5f, 0.0f, 0.0f);

		glVertex3f(-0.375f, 0.25f, 0.0f);
		glVertex3f(0.375f, 0.25f, 0.0f);

		glVertex3f(-0.25f, 0.0f, 0.0f);
		glVertex3f(0.0f, -0.75f, 0.0f);

		glVertex3f(0.25f, 0.0f, 0.0f);
		glVertex3f(0.0f, -0.75f, 0.0f);

		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, -0.75f, 0.0f);

	glEnd();

	glColor3f(1.0f, 1.0f, 0.0f); //yellow color

	glBegin(GL_LINE_LOOP); //starts drawing of line loop
		glVertex3f(-0.5f, 0.0f, 0.0f);
		glVertex3f(0.5f, 0.0f, 0.0f);
		glVertex3f(0.0f, -0.75f, 0.0f);
	glEnd();//end drawing of points

	//ensures our objects are drawn right away
	glFlush(); 

	//if we are using double buffering
	glutSwapBuffers(); 
}

int main(int argc, char ** argv )
{
	glutInit(&argc, argv); //process arguments

	//Initialize buffers
	glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE ); 
	
	//Sets some initial stuff
	glutInitWindowPosition(400, 200 ); 
	glutInitWindowSize(800, 600);

	//Creates window
	static int window = glutCreateWindow( "Part II question II - Shane"); 

	//Display callback function, etc. myRender()
	glutDisplayFunc(MyRender);

	//Enters main processing loop
	glutMainLoop(); 

	exit(0);
}