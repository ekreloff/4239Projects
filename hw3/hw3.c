/* *******************************************************
 * Created By Ethan Kreloff January 27, 2014.
 * *******************************************************
 * Based off of code from CSCI 5239/4239 Advanced Computer
 * Graphics at the University of Colorado, Boulder.
 * *******************************************************
 * Calls glut and gl functions to draw bomber
 * *******************************************************
 * hw2.c
 * ******************************************************/



#include "CSCIx239.h"
#include "print.c"
#include "project.c"
#include "fatal.c"
#include "shader.c"


/*
 *  Global variables 
 */

int shadeMode = 0; //Shader Mode
int th=0;         //  Azimuth of view angle
int ph=0;         //  Elevation of view angle
int fov=55;       //  Field of view (for perspective)
int axes = 1;     //  Display axes
double asp=1;     //  Aspect ratio
double dim=5.0;   //  Size of world
double X  = 0;   //  Location
double Y  = 0;   //  Location
double Z  = 0;   //  Location
double zoom = 1;  //Scaling factor
int shader[] = {0,0};



void Bomber(){
    
    //  Base
    glBegin(GL_POLYGON);
    
    glColor3f(.2,.2,.2);
    
    glVertex3f(5,0,0);
    glVertex3f(1,0,-2);
    glVertex3f(-2,0,-1.5);
    glVertex3f(-3,0,0);
    glVertex3f(-2,0,1.5);
    glVertex3f(1,0,2);
    
    glEnd();
    
    //  Left Wing
    glBegin(GL_POLYGON);
    
    glVertex3f(1,0,-2);
    glVertex3f(-2.8,0,-4);
    glVertex3f(-3.1,0,-4);
    glVertex3f(-3.3,0,-3.3);
    glVertex3f(.3,0,0);
    
    glEnd();
    
    //  Right Wing
    glBegin(GL_POLYGON);
    
    glVertex3f(1,0,2);
    glVertex3f(.3,0,0);
    glVertex3f(-3.3,0,3.3);
    glVertex3f(-3.1,0,4);
    glVertex3f(-2.8,0,4);
    
    glEnd();
    
    
    //  Front feature 1 right
    glBegin(GL_POLYGON);
    
    glColor3f(0,1,0);
    
    glVertex3f(5,0,0);
    glVertex3f(3,.65,0);
    glVertex3f(4.5,0,.25);
    
    glEnd();
    
    //  Front feature 1 left
    glBegin(GL_POLYGON);
    
    glVertex3f(5,0,0);
    glVertex3f(3,.65,0);
    glVertex3f(4.5,0,-.25);
    
    glEnd();
    
    //Front feature 2 right
    glBegin(GL_POLYGON);
    
    glColor3f(1,1,0);
    
    glVertex3f(2.5,1.1,0);
    glVertex3f(4.5,0,.25);
    glVertex3f(4,0,.5);
    
    glEnd();
    
    //Front feature 2 left
    glBegin(GL_POLYGON);
    
    glColor3f(1,1,0);
    
    glVertex3f(2.5,1.1,0);
    glVertex3f(4.5,0,-.25);
    glVertex3f(4,0,-.5);
    
    glEnd();
    
    //Front feature 2 middle
    glBegin(GL_POLYGON);
    
    glColor3f(.8,.8,0);
    
    glVertex3f(2.5,1.1,0);
    glVertex3f(4.5,0,.25);
    glVertex3f(4.5,0,-.25);
    
    glEnd();
    
    //side feature right
    glBegin(GL_POLYGON);
    
    glColor3f(0,0,1);
    
    glVertex3f(4,0,.5);
    glVertex3f(-1.6,0,1.7);
    glVertex3f(-1,.3,1.35);
    glVertex3f(2.5,1.1,0);
    
    glEnd();
    
    //side feature left
    glBegin(GL_POLYGON);
    
    glVertex3f(4,0,-.5);
    glVertex3f(-1.6,0,-1.7);
    glVertex3f(-1,.3,-1.35);
    glVertex3f(2.5,1.1,0);
    
    glEnd();
    
    //top feature left
    glBegin(GL_POLYGON);
    
    glColor3f(0,1,1);
    
    glVertex3f(2.5,1.1,0);
    glVertex3f(-3,.6,0);
    glVertex3f(-1,.3,-1.35);
    
    glEnd();
    
    //top feature right
    glBegin(GL_POLYGON);
    
    glVertex3f(2.5,1.1,0);
    glVertex3f(-3,.6,0);
    glVertex3f(-1,.3,1.35);
    
    glEnd();
    
    //back feature right
    glBegin(GL_POLYGON);
    
    glColor3f(1,0,1);
    
    glVertex3f(-3,.6,0);
    glVertex3f(-3,0,0);
    glVertex3f(-2,0,1.5);
    glVertex3f(-1.6,0,1.7);
    glVertex3f(-1,.3,1.35);
    
    glEnd();
    
    //back feature left
    glBegin(GL_POLYGON);
    
    glVertex3f(-3,.6,0);
    glVertex3f(-3,0,0);
    glVertex3f(-2,0,-1.5);
    glVertex3f(-1.6,0,-1.7);
    glVertex3f(-1,.3,-1.35);
    
    glEnd();
    
    
    //wing left
    glBegin(GL_POLYGON);
    
    glColor3f(.2,.2,.2);
    
    glVertex3f(-3,.6,0);
    glVertex3f(-2,.4,-.2);
    glVertex3f(-3,2.2,-1);
    glVertex3f(-3.5,2.5,-.8);
    
    glEnd();
    
    //wing right
    glBegin(GL_POLYGON);
    
    glVertex3f(-3,.6,0);
    glVertex3f(-2,.4,.2);
    glVertex3f(-3,2.2,1);
    glVertex3f(-3.5,2.5,.8);
    
    glEnd();
    
    
}


/*
 *  OpenGL (GLUT) calls this routine to display the scene
 */
void display()
{
   
   //  Erase the window and the depth buffer
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   //  Enable Z-buffering in OpenGL
   glEnable(GL_DEPTH_TEST);
   //  Undo previous transformations
   glLoadIdentity();
   //  Perspective - set eye position
    double Ex = -2*dim*Sin(th)*Cos(ph);
    double Ey = +2*dim        *Sin(ph);
    double Ez = +2*dim*Cos(th)*Cos(ph);
    gluLookAt(Ex+X,Ey+Y,Ez+Z , X,Y,Z , 0,Cos(ph),0);
    
    //  Select shader (0 => no shader)
    glUseProgram(shader[shadeMode]);
 
    //Draw Bomber
    glPushMatrix();
    glTranslated(X,Y,Z);
    glColor3f(1,1,0);
    glScaled(zoom,zoom,zoom);
    Bomber();
    glPopMatrix();
    
    //  No shader for axes
    glUseProgram(0);
    
    
    //  Draw axes
   
    glColor3f(1,1,1);
    
   if (axes)
   {
      const double len=5;  //  Length of axes
       
       
       
      glBegin(GL_LINES);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(len,0.0,0.0);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(0.0,len,0.0);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(0.0,0.0,len);
      glEnd();
      //  Label axes
      glRasterPos3d(len,0.0,0.0);
      Print("X");
      glRasterPos3d(0.0,len,0.0);
      Print("Y");
      glRasterPos3d(0.0,0.0,len);
      Print("Z");
   }
   //  Display parameters
   glWindowPos2i(5,5);
   Print("Angle=%d,%d  Dim=%.1f FOV=%d ",th,ph,dim,fov);
   //  Render the scene and make it visible
   glFlush();
   glutSwapBuffers();
}

/*
 *  GLUT calls this routine when an arrow key is pressed
 */
void special(int key,int x,int y)
{
   //  Right arrow key - increase angle by 5 degrees
   if (key == GLUT_KEY_RIGHT)
      th += 5;
   //  Left arrow key - decrease angle by 5 degrees
   else if (key == GLUT_KEY_LEFT)
      th -= 5;
   //  Up arrow key - increase elevation by 5 degrees
   else if (key == GLUT_KEY_UP)
      ph += 5;
   //  Down arrow key - decrease elevation by 5 degrees
   else if (key == GLUT_KEY_DOWN)
      ph -= 5;
   //  PageUp key - increase dim
   else if (key == GLUT_KEY_PAGE_UP)
      dim += 0.1;
   //  PageDown key - decrease dim
   else if (key == GLUT_KEY_PAGE_DOWN && dim>1)
      dim -= 0.1;
   //  Keep angles to +/-360 degrees
   th %= 360;
   ph %= 360;
   //  Update projection
    Project(fov,asp,dim);
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when a key is pressed
 */
void key(unsigned char ch,int x,int y)
{
   //  Exit on ESC
   if (ch == 27)
      exit(0);
   //  Reset view angle
   if (ch == 'x'){
      th = ph = X = Y = Z = 0;
       zoom = 1;
   }
   //  Change field of view angle
   if (ch == '-' && ch>1)
      fov--;
   if (ch == '+' && ch<179)
      fov++;
   if (ch == 'm' || ch == 'M')
      shadeMode = (shadeMode+1)%2;
    
    //Zoom
   if (ch == 'i')
        zoom += .1;
   if(ch == 'o')
       if(zoom > .2)
           zoom -= .1;
    
    
    //Change axis on and off
    if (ch == 'z') axes = !axes;
    
    
   //  Reproject
    Project(fov,asp,dim);
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when the window is resized
 */
void reshape(int width,int height)
{
   //  Ratio of the width to the height of the window
   asp = (height>0) ? (double)width/height : 1;
   //  Set the viewport to the entire window
   glViewport(0,0, width,height);
   //  Set projection
    Project(fov,asp,dim);
}

/*
 *  Start up GLUT and tell it what to do
 */
int main(int argc,char* argv[])
{
   //  Initialize GLUT
   glutInit(&argc,argv);
   //  Request double buffered, true color window with Z buffering at 600x600
   glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
   glutInitWindowSize(600,600);
   glutCreateWindow("Assignment 3: Ethan Kreloff");
   //  Set callbacks
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutSpecialFunc(special);
   glutKeyboardFunc(key);
    
   //  Create Shader Prog
   shader[1] = CreateShaderProg("shader1.vert",NULL);

   //  Pass control to GLUT so it can interact with the user
   glutMainLoop();
   return 0;
}
