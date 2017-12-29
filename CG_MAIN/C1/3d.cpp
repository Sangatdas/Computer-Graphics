#include <iostream>
#include <GL/glut.h>

GLfloat xrotate=0.0,yrotate=0.0,zrotate=0.0;
GLfloat tx=0.0,ty=0.0,tz=0.0,sx=1.0,sy=1.0,sz=1.0;


void redisplayFunc()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glColor3f(0.9,0.9,0.0);
	glTranslatef(tx+0.0,ty+0.0,tz-3.0);
	glRotatef(xrotate,1.0,0.0,0.0);
	glRotatef(yrotate,0.0,1.0,0.0);
	glRotatef(zrotate,0.0,0.0,1.0);
	glScalef(sx,sy,sz);
	glutWireCube(0.75);
}

void reshapeFunc(int x,int y)
{
	if(x==0||y==0)	return;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40,(GLdouble)x/(GLdouble)y,0.5,20.0);
	glMatrixMode(GL_MODELVIEW);
	glViewport(0,0,x,y);
}

void KeyboardFunc(unsigned char key,int x,int y)
{
	if(key==27)
		exit(0);
	switch(key)
	{
		case 'b':
			tz-=0.1f;
			break;
		case 'f':
			tz+=0.1f;
			break;
		case 'x':
			xrotate+=0.1f;
			break;
		case 'y':
			yrotate+=0.1f;
			break;
		case 'z':
			zrotate+=0.1f;
			break;
		case '1':
			sx-=0.1f;
			break;
		case '2':
			sy-=0.1f;
			break;
		case '3':
			sz-=0.1f;
			break;
		case '7':
			sx+=0.1f;
			break;
		case '8':
			sy+=0.1f;
			break;
		case '9':
			sz+=0.1f;
			break;
	}
}

void SpecialFunc(int key,int x,int y)
{
	switch(key)
	{
		case GLUT_KEY_LEFT:
			tx-=0.1f;
			break;
		case GLUT_KEY_RIGHT:
			tx+=0.1f;
			break;
		case GLUT_KEY_UP:
			ty+=0.1f;
			break;
		case GLUT_KEY_DOWN:
			ty-=0.1f;
			break;
	}
}

void idleFunc()
{
	glutKeyboardFunc(KeyboardFunc);
	glutSpecialFunc(SpecialFunc);
	redisplayFunc();
}

int main(int argc,char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(1024,512);
	glutCreateWindow("3D cube");
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	glClearColor(0.0,0.0,0.0,1.0);
	glutDisplayFunc(redisplayFunc);
	glutReshapeFunc(reshapeFunc);
	glutIdleFunc(idleFunc);
	glutMainLoop();
	return 0;
}
