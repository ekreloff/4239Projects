/* *******************************************************
 * Created By Ethan Kreloff January 21, 2014.
 * *******************************************************
 * Based off of code from CSCI 5239/4239 Advanced Computer
 * Graphics at the University of Colorado, Boulder.
 * *******************************************************
 * OpenGL display for visual calculation. 
 * *******************************************************
 * visual.cpp
 * ******************************************************/
 
#include <QtOpenGL>
#include <QSize>
#include "visual.h" 

Visual::Visual(QWidget* parent) 
{
	// Set instance variables
	firstNumber = 0;
}

void Visual::setNumber(double number)
{
	// Slot
	firstNumber = number;
}

void Visual::initializeGL()
{
   //  Enable Z-buffer test
   glEnable(GL_DEPTH_TEST);
}

void Visual::resizeGL(int width, int height)
{
	// Resize code
	
	//  Window aspect ration
   float asp= height ? width / (float)height : 1;

   //  Viewport is whole screen
   glViewport(0,0,width,height);

   //  Orthogonal projection to 1.5
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-25.0*asp, +25.0*asp, -25.0, +25.0, -25.0, +25.0);

   //  Back to model view
   glMatrixMode(GL_MODELVIEW);
}

void Visual::paintGL()
{
	//  Clear screen and Z-buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //  Reset transformations
    glLoadIdentity();
    
    //glFrustum(-1.0, 1.0, -1.0, 100.0, 0.0, 300.0);
    QSize viewSize = sizeHint();
    glOrtho( -1.0, +1.0, -1.0, +1.0, -1.0, 1.0 );
    //glOrtho(-(viewSize.width()/2), (viewSize.width()/2), -(viewSize.height()/2), (viewSize.height()/2), -1.0, 1.0 );
    
    //  Draw RGB triangle
    for(int i = firstNumber; i > 0; i--){
		glBegin(GL_TRIANGLES);
		glColor3f(1,0,0); glVertex3d(-35, -20+i*.1,5.0);
		glColor3f(0,1,1); glVertex3d(-45,-24+i*.1,0);
		glColor3f(1,0,1); glVertex3d(-25,-24+i*.1,0);
		glEnd();
	}
    
    
}
