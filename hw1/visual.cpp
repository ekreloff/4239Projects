/* *******************************************************
 * Created By Ethan Kreloff January 21, 2014.
 * *******************************************************
 * Based off of code from CSCI 5239/4239 Advanced Computer
 * Graphics at the University of Colorado, Boulder and 
 * examples from qt-project.org.
 * *******************************************************
 * OpenGL display for visual calculation. 
 * *******************************************************
 * visual.cpp
 * ******************************************************/
 
#include <QtOpenGL>
#include <QSize>
#include "visual.h" 

#define NORMALIZE 100

Visual::Visual(QWidget* parent) 
{
	(void) parent; //unused
	
	// Set instance variables
	firstOperand = secondOperand = result = 0;
}

void Visual::initializeGL()
{
   //  Enable Z-buffer test
   glEnable(GL_DEPTH_TEST);
}

void Visual::resizeGL(int width, int height)
{
	//  Window aspect ration
   float asp= height ? width / (float)height : 1;

   //  Viewport is whole screen
   glViewport(0,0,width,height);

   //  Orthogonal projection to 1.5
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-25.0*asp, +25.0*asp, -25.0, +25.0, -25.0, +25.0);
   //glFrustum(-1.0/*asp*/, +1.0/*asp*/, -1.0, +1.0, -1.0, +1.0);
   //  Back to model view
   glMatrixMode(GL_MODELVIEW);
}

void Visual::paintGL()
{
	//  Clear screen and Z-buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //  Reset transformations
    glLoadIdentity();
    
    // Draw bars
    cube(-35, -15, 0, 0, firstOperand, 0);
    cube(-10, -15, 0, 0, secondOperand, 0);
    cube(+30, -15, 0, 0, result, 0);
}

void Visual::cube(int x, int y, int z, 
				  int sx, int sy, int sz)
{
   //  Front
   
   sy = sy/NORMALIZE;
   
   glLoadIdentity();
   glTranslated(x, y, z);
   glRotated(45,1,0,0);
   glRotated(45,0,1,0);
   glColor3f(0,0,1);
   glBegin(GL_QUADS);
   glNormal3f( 0, 0,+1);
   glTexCoord2f(0,0); glVertex3f(-1+sx,-1,+1+sz);
   glTexCoord2f(1,0); glVertex3f(+1,-1,+1);
   glTexCoord2f(1,1); glVertex3f(+1,sy,+1);
   glTexCoord2f(0,1); glVertex3f(-1,sy,+1);
   glEnd();
   //  Back
   glColor3f(1,0,0);
   glBegin(GL_QUADS);
   glNormal3f( 0, 0,-1);
   glTexCoord2f(0,0); glVertex3f(+1,-1,-1);
   glTexCoord2f(1,0); glVertex3f(-1,-1,-1);
   glTexCoord2f(1,1); glVertex3f(-1,sy,-1);
   glTexCoord2f(0,1); glVertex3f(+1,sy,-1);
   glEnd();
   //  Right
   glColor3f(1,0,0);
   glBegin(GL_QUADS);
   glNormal3f(+1, 0, 0);
   glTexCoord2f(0,0); glVertex3f(+1,-1,+1);
   glTexCoord2f(1,0); glVertex3f(+1,-1,-1);
   glTexCoord2f(1,1); glVertex3f(+1,sy,-1);
   glTexCoord2f(0,1); glVertex3f(+1,sy,+1);
   glEnd();
   //  Left
   glColor3f(0,0,1);
   glBegin(GL_QUADS);
   glNormal3f(-1, 0, 0);
   glTexCoord2f(0,0); glVertex3f(-1,-1,-1);
   glTexCoord2f(1,0); glVertex3f(-1,-1,+1);
   glTexCoord2f(1,1); glVertex3f(-1,sy,+1);
   glTexCoord2f(0,1); glVertex3f(-1,sy,-1);
   glEnd();
   //  Top
   glColor3f(1,0,0);
   glBegin(GL_QUADS);
   glNormal3f( 0,+1, 0);
   glTexCoord2f(0,0); glVertex3f(-1,sy,+1);
   glTexCoord2f(1,0); glVertex3f(+1,sy,+1);
   glTexCoord2f(1,1); glVertex3f(+1,sy,-1);
   glTexCoord2f(0,1); glVertex3f(-1,sy,-1);
   glEnd();
   //  Bottom
   glColor3f(1,0,0);
   glBegin(GL_QUADS);
   glNormal3f( 0,-1, 0);
   glTexCoord2f(0,0); glVertex3f(-1,-1,-1);
   glTexCoord2f(1,0); glVertex3f(+1,-1,-1);
   glTexCoord2f(1,1); glVertex3f(+1,-1,+1);
   glTexCoord2f(0,1); glVertex3f(-1,-1,+1);
   glEnd();
}

void Visual::setNumber(int number, int operation){
	switch(operation){
	case 0:
		firstOperand = number;
		break;
	case 1:
		secondOperand = number;
		break;
	case 2:
		result = number;
		break;
	}
	updateGL();
}
