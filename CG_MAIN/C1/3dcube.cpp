#include <GL/glut.h>
#include <iostream>
#include <cstring>

using namespace std;

GLfloat xRotated = 0.0, yRotated = 0.0, zRotated = 0.0;

GLfloat tx = 0.0, ty = 0.0, tz = 0.0, sx = 1.0, sy = 1.0, sz = 1.0;



void redisplayFunc(void)
{
    glClear(GL_COLOR_BUFFER_BIT);       //to get assigned window color to be displayed
    glLoadIdentity();			//Initialize matrix
    glTranslatef(tx+0.0,ty+0.0,tz-3.0);
    glColor3f(0.9, 0.9, 0.0); 
    glRotatef(xRotated,1.0,0.0,0.0);
    glRotatef(yRotated,0.0,1.0,0.0);
    glRotatef(zRotated,0.0,0.0,1.0);
    glScalef(sx,sy,sz);
    glutWireCube(0.75);
    //glFlush();        			//Flush buffers to the screen
    //glutSwapBuffers();
}

void reshapeFunc(int x, int y)
{
    if (y == 0 || x == 0) return;  //Nothing is visible then, so return
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity();
    /*
    Angle of view=40 degrees
    Near clipping plane distance 0.5
    Far clipping distance 20.0*/
    gluPerspective(40.0,(GLdouble)x/(GLdouble)y,0.5,20.0);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0,0,x,y);  //Use the whole window for rendering
}

void KeyboardFunc(unsigned char key, int x, int y) {
	if(key == 27)
		exit(0);	
	switch(key) {
		case 'n':
			tz = tz;
			break;
		case 'b':
			tz -= 0.01f;
			break;
		case 'f':
			tz += 0.01f;
			break;
		case 'x':
			xRotated += 0.1f;
			break;
		case 'y':
			yRotated += 0.1f;
			break;
		case 'z':
			zRotated += 0.1f;
			break;
		case '1':
			sx -= 0.1f;
			break;
		case '2':
			sy -= 0.1f;
			break;
		case '3':
			sz -= 0.1f;
			break;
		case '7':
			sx += 0.1f;
			break;
		case '8':
			sy += 0.1f;
			break;
		case '9':
			sz += 0.1f;
			break;
	}
}

void SpecialFunc(int key, int x, int y) {
	switch(key) {
		case GLUT_KEY_LEFT:		
			tx -= 0.01f;
			break;	
		case GLUT_KEY_RIGHT:
			tx += 0.01f;
			break;
		case GLUT_KEY_DOWN:
			ty -= 0.01f;
			break;
		case GLUT_KEY_UP:
			ty += 0.01f;
			break;
	}
}

void idleFunc(void)
{
	glutKeyboardFunc(KeyboardFunc);
	glutSpecialFunc(SpecialFunc);
    redisplayFunc();
}

int main (int argc, char **argv)
{	
    glutInit(&argc, argv);	
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);	//Double buffering used to avoid flickering in animation
    glutInitWindowSize(1024,768);           //Set initial Window height and width
    glutCreateWindow("Cube3d Transformation");       //Window title bar
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glClearColor(0.0, 0.0, 0.0, 1.0);       //Set window color
    glutDisplayFunc(redisplayFunc);         //image to be displayed in window
    glutReshapeFunc(reshapeFunc);		//glutReshapeFunc sets the reshape callback for the current window.
    glutIdleFunc(idleFunc);
    glutMainLoop();             //Displays the initial graphics and puts the program into an infinite loop
    return 0;
}

