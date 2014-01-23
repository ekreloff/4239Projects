//
//  OpenGL Triangle widget
//
#include <QtOpenGL>
#include <GL/glu.h>

#include "calcdisplay.h"

//
//  Constructor
//
CalcDisplay::CalcDisplay(QWidget* parent)
{
	firstButton = false;
	secondButton = false;
	/*
	this->display(5);	
	this->display(this->value() + 1);
	*/
}

void CalcDisplay::button1Click()
{
	this->display(1);
}


void CalcDisplay::button2Click()
{
	this->display(2);
}

void CalcDisplay::button3Click()
{
	this->display(3);
}
	
void CalcDisplay::button4Click()
{
	this->display(4);
}

void CalcDisplay::button5Click()
{
	this->display(5);
}
	
void CalcDisplay::button6Click()
{
	this->display(6);
}

void CalcDisplay::button7Click()
{
	this->display(7);
}

void CalcDisplay::button8Click()
{
	this->display(8);
}

void CalcDisplay::button9Click()
{
	this->display(9);
}

void CalcDisplay::button0Click()
{
	this->display(0);
}

void CalcDisplay::buttonPlusClick()
{
	this->display(19203);
}

void CalcDisplay::buttonMinusClick()
{
	this->display(1);
}

void CalcDisplay::buttonTimesClick()
{
	this->display(1);
}

void CalcDisplay::buttonDivideClick()
{
	this->display(1);
}

void CalcDisplay::buttonEqualsClick()
{
	this->display(1);
}

void CalcDisplay::buttonClearClick()
{
	this->display(1);
}
	






/*
void Football::setPan(int distance){
	pan = distance/10.0;
	updateGL();
}

//
//  Set theta (rotation angle)
//

void Triangle::setTheta(int angle)
{
   //  Set angle
   theta = angle;
   //  Request redisplay
   updateGL();
}

//
//  Set color or texture
//
void Triangle::setType(QString type)
{
   //  Set toggle
   texture = type.contains(tr("Texture"));
   //  Request redisplay
   updateGL();
}

//
//  Initialize

void Football::initializeGL()
{
   //  Enable Z-buffer depth testing
   glEnable(GL_DEPTH_TEST);
   
   //  Load Darth texture
   QPixmap img("darth.jpg");
   darth = bindTexture(img,GL_TEXTURE_2D);
   
}




//
//  Set projection when window is resized
//

void Football::resizeGL(int width, int height)
{
   //  Window aspect ration
   float asp= height ? width / (float)height : 1;

   //  Viewport is whole screen
   glViewport(0,0,width,height);

   //  Orthogonal projection to 1.5
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-1.5*asp, +1.5*asp, -1.5, +1.5, -1.5, +1.5);

   //  Back to model view
   glMatrixMode(GL_MODELVIEW);
}

//
//  Draw the window
//
void Football::paintGL()
{
    //  Clear screen and Z-buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //  Reset transformations
    //glLoadIdentity();
    
    gluLookAt(-4.0, pan, 0.0,
			  0.0, -1.0, 0.0,
			  0.0, 1.0, 0.0);
	
	
	glLoadIdentity();
	
    //  Draw RGB triangle
    glBegin(GL_TRIANGLES);
    glColor3f(1,0,0); glVertex3d( pan, 0.2,0);
    glColor3f(0,1,0); glVertex3d(pan-.2,-.2,0);
    glColor3f(0,0,1); glVertex3d(pan+.2,-.2,0);
    glEnd();
    
     //  Draw axes in white
   glColor3f(1,1,1);
   glBegin(GL_LINES);
   glVertex3d(0,0,0);
   glVertex3d(1,0,0);
   glVertex3d(0,0,0);
   glVertex3d(0,1,0);
   glVertex3d(0,0,0);
   glVertex3d(0,0,1);
   glEnd();

	
    //  Set rotation
    glRotated(theta , 1,1,0);

    //  Draw textured triangle
    if (texture)
    {
       glBindTexture(GL_TEXTURE_2D,darth);
       glEnable(GL_TEXTURE_2D);
       glColor3f(1,1,1);
       glBegin(GL_TRIANGLES);
       glTexCoord2d(0.5,1.0); glVertex3d( 0, 1,1);
       glTexCoord2d(0.0,0.0); glVertex3d(-1,-1,1);
       glTexCoord2d(1.0,0.0); glVertex3d(+1,-1,1);
       glEnd();
       glDisable(GL_TEXTURE_2D);
    }
    //  Draw CMY triangle
    else
    {
       glBegin(GL_TRIANGLES);
       glColor3f(1,1,0); glVertex3d( 0, 1,1);
       glColor3f(0,1,1); glVertex3d(-1,-1,1);
       glColor3f(1,0,1); glVertex3d(+1,-1,1);
       glEnd();
    }

   //  Emit message to display
   emit message("Display at angle "+QString::number(theta)+" degrees");
   
}*/