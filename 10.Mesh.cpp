#include<GL/glut.h>
#include<stdio.h>
float r=1,c=1.3,i,j;
void dis()
{
	glClear(GL_COLOR_BUFFER_BIT);
	for(i=0.0;i<c;i=i+0.1)
	{
		glBegin(GL_LINE_STRIP);
			for(j=0.0;j<r;j=j+0.1)
				glVertex2f(i-0.9,j-0.9);
		glEnd();
	}
	for(i=0.0;i<r;i=i+0.1)
	{
		glBegin(GL_LINE_STRIP);
			for(j=0.0;j<c;j=j+0.1)
				glVertex2f(j-0.9,i-0.9);
		glEnd();
	}
	glFlush();
}
void main()
{	glutInit(&argc,argv);
	glutCreateWindow("mesh");
	glutInitWindowSize(900,600);
	
	glutDisplayFunc(dis);
	glutMainLoop();
}
