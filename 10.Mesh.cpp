#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<GL/glut.h>

static GLfloat shooter[5][2]={{40,10},{80,10},{80,15},{60,19.5},{40,15}};
static GLfloat bul[10][2];
int activebulletcount;
int score = 0;
int hiscore = 0;
bool gameover;
char buffer[50];

typedef struct
{
	int x1,y1,x2,y2;
	int color;
	int lives;
}bricktype;

bricktype br[15][30];
GLfloat colorarr[][4]={{0.8,0.8,0.8},{1.0,0.0,0.0},{0.0,1.0,0.0},{0.0,0.0,1.0}};
int currbullet=6;

//Function to write characters on opengl window 
void drawString (void * font, char *s, float x, float y)
{
    unsigned int i;
    glRasterPos2f(x, y);
    for (i = 0; i < strlen (s); i++)
        glutBitmapCharacter (font, s[i]);
}


void brick(int x0,int y0,int x1,int y1,int col)
{
	br[x0/40][y0/20].x1=x0;
	br[x0/40][y0/20].y1=y0;
	br[x0/40][y0/20].x2=x1;
	br[x0/40][y0/20].y2=y1;
	br[x0/40][y0/20].color=col;
	br[x0/40][y0/20].lives=col;
}


int brickline(int y0,int y1)
{
   int x0=0,x1=40,i;
   int x;
   for(i=0;i<15;i++)
   {
   		x=1+rand()%3;
        brick(x0,y0,x1,y1,x);
        x0=x0+40;
        x1=x1+40;
   }

   return 1;
}


void translatedown()
{
	int x0,y0;
	for(x0=0;x0<=560;x0+=40)
		if(br[x0/40][2].lives > 0 && br[x0/40][2].color != 0)
			gameover = true;


	for(x0=0;x0<=560;x0+=40)
		for(y0=20;y0<=580;y0+=20)
		{
			br[x0/40][(y0-20)/20].x1=br[x0/40][y0/20].x1;
			br[x0/40][(y0-20)/20].y1=br[x0/40][y0/20].y1-20;
			br[x0/40][(y0-20)/20].x2=br[x0/40][y0/20].x2;
			br[x0/40][(y0-20)/20].y2=br[x0/40][y0/20].y2-20;
			br[x0/40][(y0-20)/20].color=br[x0/40][y0/20].color;
			br[x0/40][(y0-20)/20].lives=br[x0/40][y0/20].lives;
		}
}


static int y0=580,y1=560;


void updatebullet(int value)
{
	int i;
	glutTimerFunc(40, updatebullet, 0);
	if(gameover == false)
	{
		if(activebulletcount < 10)
		{
			bul[activebulletcount][0]=shooter[3][0];
			bul[activebulletcount][1]=shooter[3][1] - 20;
			activebulletcount = activebulletcount + 1;
		}

		for(i=0;i<activebulletcount;i++)
		{
		  bul[i][1]+=20;
		  if(bul[i][1] > 600)
		  {
				bul[i][0]=shooter[3][0];
				bul[i][1]=shooter[3][1];
		  }
		}
	}
}


void bullet(int value)
{
	if(gameover == false)
	{
		currbullet+=1;
        currbullet=currbullet%20;
	
	   if(currbullet%2==0)
       {
    		translatedown();
    		brickline(y0,y1);
       }
	}
    glutTimerFunc(1000,bullet,1);
}


void idle()
{
	int i;
	for(i=0;i<10;i++)
  	{
		if((bul[i][1]<600)&&(br[((int)bul[i][0])/40][((int)bul[i][1])/20 + 1].lives>0))
		{
			score = score + 100;
			if(score > hiscore)
				hiscore = score;

			br[((int)bul[i][0])/40][((int)bul[i][1])/20 + 1].lives-=1;
			bul[i][0]=shooter[3][0];
			bul[i][1]=shooter[3][1];
	  	}
    }
  	glutPostRedisplay();
}


void gun()
{
	glColor3f(1.0,0.6,0.1);
	glBegin(GL_POLYGON);
	glVertex2f(shooter[0][0],shooter[0][1]);
	glVertex2f(shooter[1][0],shooter[1][1]);
	glVertex2f(shooter[2][0],shooter[2][1]);
	glVertex2f(shooter[3][0],shooter[3][1]);
	glVertex2f(shooter[4][0],shooter[4][1]);
	glEnd();
}


void drawbricks()
{
	int x0,y0;
	for(x0=0;x0<=560;x0+=40)
		for(y0=580;y0>=0;y0-=20)
			if(br[x0/40][y0/20].lives>=1)
			{
				glColor3fv(colorarr[br[x0/40][y0/20].color]);
				glBegin(GL_POLYGON);
				glVertex2i(br[x0/40][y0/20].x1,br[x0/40][y0/20].y1);
				glVertex2i(br[x0/40][y0/20].x2,br[x0/40][y0/20].y1);
				glVertex2i(br[x0/40][y0/20].x2,br[x0/40][y0/20].y2);
				glVertex2i(br[x0/40][y0/20].x1,br[x0/40][y0/20].y2);
				glEnd();
			}
			else 
			{
				glColor3fv(colorarr[0]);
				glBegin(GL_POLYGON);
				glVertex2i(br[x0/40][y0/20].x1,br[x0/40][y0/20].y1);
				glVertex2i(br[x0/40][y0/20].x2,br[x0/40][y0/20].y1);
				glVertex2i(br[x0/40][y0/20].x2,br[x0/40][y0/20].y2);
				glVertex2i(br[x0/40][y0/20].x1,br[x0/40][y0/20].y2);
				glEnd();
			}
}


void display()
{		
	int i;
	glClear(GL_COLOR_BUFFER_BIT);
	drawbricks();
	for(i=0;i<activebulletcount;i++)
	{
		glColor3f(0.0,0.0,0.0);
	    glBegin(GL_POINTS);
	    glVertex2d(bul[i][0],bul[i][1]);
	    glEnd();
    }
    gun();

    glColor3f(0, 0, 0);
	drawString(GLUT_BITMAP_HELVETICA_18, "Score:", 25, 585);	
	itoa(score, buffer, 10);
	drawString(GLUT_BITMAP_HELVETICA_18, buffer, 85, 585);

	glColor3f(0, 0, 0);
	drawString(GLUT_BITMAP_HELVETICA_18, "Hi-Score:", 380, 585);	
	itoa(hiscore, buffer, 10);
	drawString(GLUT_BITMAP_HELVETICA_18, buffer, 470, 585);

	if(gameover == true)
	{
		glColor3f(1, 1, 1);
		drawString(GLUT_BITMAP_HELVETICA_18, "Game Over", 250, 280); //display Game Over on the screen
		drawString(GLUT_BITMAP_HELVETICA_18, "Do you want to continue(y/n)", 180, 310); //display GDo you want to continue(y/n) on the screen
	}

   glutSwapBuffers();
}


void resetBricks()
{
	int x0,y0;
	score = 0;
	for(x0=0;x0<=560;x0+=40)
		for(y0=580;y0>=0;y0-=20)
		{
			br[x0/40][y0/20].x1=0;
			br[x0/40][y0/20].y1=0;
			br[x0/40][y0/20].x2=0;
			br[x0/40][y0/20].y2=0;
			br[x0/40][y0/20].color=0;
			br[x0/40][y0/20].lives=0;
		}
}


void myinit()
{
	glClearColor(0.8,0.8,0.8,1.0);
	glMatrixMode(GL_PROJECTION);
	glColor3f(1.0,0.0,0.0);
	glPointSize(7.0);
	gluOrtho2D(0.0,599.0,0.0,599.0);
	glMatrixMode(GL_MODELVIEW);
	resetBricks();
}


void Keys(int key,int x,int y)
{
	int j;
	if(gameover == false)
	{
		switch(key)
		{
			case GLUT_KEY_LEFT:if(shooter[0][0]>=40)
								{
									for(j=0;j<5;j++)
        								shooter[j][0]-=40;
									glutPostRedisplay();
							  	}
								break;
			case GLUT_KEY_RIGHT:if(shooter[0][0]<560)
								{
									for(j=0;j<5;j++)
											shooter[j][0]+=40;
									glutPostRedisplay();
								}
								break;
		}
	}
}


void keyb(unsigned char key,int x,int y)
{
    switch(key)
    {
    	case 'Q':exit(0);
    	case 'q':exit(0);
		case 'Y':
    	case 'y':
				if(gameover == true)
				{
					resetBricks();
					gameover = false;
				}
				break;
    	case 'N':
    	case 'n':
				if(gameover == true)
					exit(0);
				break;
		case 27:
		   exit(0);
       }
}


int main(int argc,char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	glutInitWindowSize(600,600);
	glutInitWindowPosition(0,0);
	glutCreateWindow("brickbreaker");
	glutDisplayFunc(display);
	glutKeyboardFunc(keyb);
	glutTimerFunc(1000,bullet,1);
	glutTimerFunc(40,updatebullet,1);
	glutIdleFunc(idle);
	glutSpecialFunc(Keys);
	myinit();
	glutMainLoop();
	return 0;
}
