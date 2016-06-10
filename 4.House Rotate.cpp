#include<GL/glut.h>
#include<stdio.h>
float v[]={	0,0.6,0.25,
		0.9,0.5,0.6,
		0,0.6,0.5,
		0.6,0.5,0,
		0.32,0,0.32,
		0.1,0.16,0.1,
		0.16,0,0.32,
		0,0,0,0,0.6};
GLubyte list[]={0,1,2,3,4,5,6,7,8,9,10,11,12};
int g=0;
void dis()
{	
	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(-100,-100,700,700);
	glDrawElements(GL_LINE_LOOP,13,GL_UNSIGNED_BYTE,list);
	glRotated(g,0,0,1);
	glDrawElements(GL_LINE_LOOP,13,GL_UNSIGNED_BYTE,list);
	glFlush();
	glLoadIdentity();
}
void main(int argc,char *argv[])
{	
	glutInit(&argc,argv);
	glutInitWindowSize(700,700);
	printf("Enter Rotation Angle:");    
	scanf("%d",&g);
	glutCreateWindow("House Optimized by R.Ganesh");
	glutDisplayFunc(dis);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2,GL_FLOAT,0,v);
	glutMainLoop();
}
