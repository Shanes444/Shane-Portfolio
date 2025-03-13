#include<GL/glut.h>
#include<GL/gl.h>
#include<GL/glu.h>

void myRender(){
	//set display window's background color 
	glClearColor(0.0, 0.0, 0.0, 0.0); 
	//clears our buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//perform any other matrix transformations here

	glColor3f(0.0f, 1.0f, 0.0f); //green color
	glLineWidth(12);
	glBegin(GL_QUADS);//start drawing a rectangle
		glVertex3f(-0.5f, 0.5f, 0.0f);//top left of window
		glVertex3f(0.5f, 0.5f, 0.0f);//top right of window
		glColor3f(1.0f, 0.0f, 1.0f);//magenta color
		glVertex3f(0.5f, -0.5f, 0.0f);//bottom right of window
		glVertex3f(-0.5f, -0.5f, 0.0f);//bottom left of window
	glEnd();//end drawing of rectangle

	glBegin(GL_TRIANGLES);//start drawing triangles
		glVertex3f(-0.5f, -0.5f, 0.0f);
		glColor3f(1.0f, 1.0f, 0.0f);//yellow color
		glVertex3f(-1.0f, 0.0f, 0.0f);
		glColor3f(0.0f, 0.0f, 1.0f);//blue color
		glVertex3f(-0.5f, 0.5f, 0.0f);
		glColor3f(1.0f, 0.0f, 1.0f);//magenta color
		glVertex3f(0.5f, -0.5f, 0.0f);
		glColor3f(1.0f, 1.0f, 0.0f);//yellow color
		glVertex3f(1.0f, 0.0f, 0.0f);
		glColor3f(0.0f, 0.0f, 1.0f);//blue color
		glVertex3f(0.5f, 0.5f, 0.0f);
	glEnd();


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
	static int window = glutCreateWindow( "Part II question I - Shane"); 

	//Display callback function, etc. myRender()
	glutDisplayFunc(myRender);

	//Enters main processing loop
	glutMainLoop(); 

	exit(0);
}