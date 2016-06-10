#include <GL/glut.h>
float v[]={-1,-1,-1,    -1,1,-1,   1,1,-1,    
            1,-1,-1,    -1,-1,1,   -1,1,1,  
			1,1,1,       1,-1,1};
float c[]={0,0,0,  1,0,0,  1,1,0,  0,1,0,  0,0,1,  1,0,1,  1,1,1,  0,1,1,};
GLubyte list[]={0,1,2,3,   2,3,7,6,   4,5,6,7,  4,5,1,0,   5,6,2,1,   0,3,7,4};
int gx=0,gy=0,gz=1;
static GLfloat theta[] = {0.0,0.0,0.0};
static GLint axis = 2;
static GLdouble viewer[]= {0.0, 0.0, 5.0}; 
void display(void)
{ glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(viewer[0],viewer[1],viewer[2], 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glRotatef(theta[0], 1.0, 0.0, 0.0);
	glRotatef(theta[1], 0.0, 1.0, 0.0);
	glRotatef(theta[2], 0.0, 0.0, 1.0);
	glDrawElements(GL_QUADS,24,GL_UNSIGNED_BYTE,list);
	glFlush();
}
void mouse(int btn, int state, int x, int y)
{	if(btn==GLUT_LEFT_BUTTON && state == GLUT_DOWN) axis = 0;
	if(btn==GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) axis = 1;
	if(btn==GLUT_RIGHT_BUTTON && state == GLUT_DOWN) axis = 2;
	theta[axis] += 2.0;
	if( theta[axis] > 360.0 ) theta[axis] -= 360.0;
	display();
}
void keys(unsigned char key, int x, int y)
{  if(key == 'x') viewer[0]-= 1.0;
   if(key == 'X') viewer[0]+= 1.0;
   if(key == 'y') viewer[1]-= 1.0;
   if(key == 'Y') viewer[1]+= 1.0;
   if(key == 'z') viewer[2]-= 1.0;
   if(key == 'Z') viewer[2]+= 1.0;
   display();
}
int main(int argc,char *argv)
{	glutInit(&argc,argv);
	glutInitWindowSize(700, 700);
	glutCreateWindow("Colorcube Viewer");
	glMatrixMode(GL_PROJECTION); 
	glFrustum(-2.0, 2.0, -2.0, 2.0, 2.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glutDisplayFunc(display);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3,GL_FLOAT,0,v);
	glColorPointer(3,GL_FLOAT,0,c);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keys);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
	return 0;
}
/******************************* THIS CODE OPTIMIZED BY R.GANESH 3PG10CS026 ****************************************/
/*********************************** http://www.facebook.com/ganeshc7 **********************************************/
