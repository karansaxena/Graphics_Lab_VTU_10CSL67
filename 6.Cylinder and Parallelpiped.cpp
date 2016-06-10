#include <math.h>
#include <GL/glut.h>
void objects(float cx,float cy,float r,int nums)
{
	//glColor3f(1,0,0);
	glBegin(GL_LINE_LOOP); //circle
	for(int ii=0;ii<nums;ii++)
	{
		float theta=2.0*3.1415926*float(ii)/float(nums);
		float x=r*cosf(theta);
		float y=r*sinf(theta);
		glVertex2f(x+cx,y+cy);
	}
	glEnd();
	//glColor3f(0,1,0);
	glBegin(GL_LINE_LOOP);  //Rectangle
	glVertex2f(0.0,0.0);
	glVertex2f(0.5,0.0);
	glVertex2f(0.5,0.5);
	glVertex2d(0.0,0.5);
	glEnd();
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(0,0,700,700);
	glTranslated(-0.4,0,0);
	for(int i=0;i<30;i++)  //No. of extrudes
	{
		glTranslated(0.01,0.01,0);
		objects(0.4,-0.7,0.3,56);
	}
	glFlush();
	glLoadIdentity();
}
int main(int argc,char *argv[])
{	glutInit(&argc,argv);
	glutInitWindowSize(700,700);
	glutCreateWindow("6Th Program Optimized by R.Ganesh");
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
