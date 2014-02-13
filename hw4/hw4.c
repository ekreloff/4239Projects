/* *******************************************************
 * Created By Ethan Kreloff February 9, 2014.
 * *******************************************************
 * Based off of code from CSCI 5239/4239 Advanced Computer
 * Graphics at the University of Colorado, Boulder.
 * *******************************************************
 * Calls glut and gl functions to a sphere
 * *******************************************************
 * hw4.c
 * ******************************************************/



#include "CSCIx239.h"
#include "print.c"
#include "project.c"
#include "fatal.c"
#include "shader.c"
#include "object.c"
#include "loadtexbmp.c"
#include "errcheck.c"
#include "fps.c"

#define MODELS 3

enum{
	
	DINO = 0,
	BUNNY = 1,
	DILLO = 2,
	SPHERE = 3
};

enum{
	DEFAULT = 1,
	INT = 2,
	IF = 3,
	FUNC = 4
};
	

/*
 *  Global variables 
 */

int shadeMode = 0; //Shader Mode
int th=0;         //  Azimuth of view angle
int ph=0;         //  Elevation of view angle
int fov=55;       //  Field of view (for perspective)
int axes = 0;     //  Display axes
int object = 0;      //  Object number
int modelID[MODELS];        //  Object model
double asp=1.0;     //  Aspect ratio
double dim=5.0;   //  Size of world
double zoom = 2.0;  //Scaling factor
int shader[] = {0,0,0,0,0,0,0}; //Shaders
char *shaderText[] = {"None", "Default", "Int", "If", "Func"};

// Lighting Variables
int lth = 90; // Lighting Azimuth
int YLight = 3; // Y component of light


/*
 *  Draw vertex in polar coordinates
 */
static void Vertex(int th,int ph)
{
   double x = -Sin(th)*Cos(ph);
   double y =  Cos(th)*Cos(ph);
   double z =          Sin(ph);
   glNormal3d(x,y,z);
   glTexCoord2d(th/360.0,ph/180.0+0.5);
   glVertex3d(x,y,z);
}

void Sphere()
{
   int th,ph;
   //  Latitude bands
   glColor3f(1,1,1);
   for (ph=-90;ph<90;ph+=5)
   {
      glBegin(GL_QUAD_STRIP);
      for (th=0;th<=360;th+=5)
      {
         Vertex(th,ph);
         Vertex(th,ph+5);
      }
      glEnd();
   }
}

/*
 *  OpenGL (GLUT) calls this routine to display the scene
 */
void display()
{
   
   //  Light position and colors
   float Emission[]  = {0.0,0.0,0.0,1.0};
   float Ambient[]   = {0.3,0.3,0.3,1.0};
   float Diffuse[]   = {1.0,1.0,1.0,1.0};
   float Specular[]  = {1.0,1.0,1.0,1.0};
   float Position[]  = {2*Cos(lth),YLight,2*Sin(lth),1.0};
   float Shinyness[] = {16};
   
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
    gluLookAt(Ex,Ey,Ez , 0,0,0 , 0,Cos(ph),0);
    
    
   //  Draw light position as sphere (still no lighting here)
   glColor3f(1,1,1);
   glPushMatrix();
   glTranslated(Position[0],Position[1],Position[2]);
   glutSolidSphere(0.03,10,10);
   glPopMatrix();
   //  OpenGL should normalize normal vectors
   glEnable(GL_NORMALIZE);
   //  Enable lighting
   glEnable(GL_LIGHTING);
   //  glColor sets ambient and diffuse color materials
   glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
   glEnable(GL_COLOR_MATERIAL);
   //  Enable light 0
   glEnable(GL_LIGHT0);
   //  Set ambient, diffuse, specular components and position of light 0
   glLightfv(GL_LIGHT0,GL_AMBIENT ,Ambient);
   glLightfv(GL_LIGHT0,GL_DIFFUSE ,Diffuse);
   glLightfv(GL_LIGHT0,GL_SPECULAR,Specular);
   glLightfv(GL_LIGHT0,GL_POSITION,Position);
   //  Set materials
   glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,Shinyness);
   glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,Specular);
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Emission);
    
    //  Select shader (0 => no shader)
    switch(shadeMode){
		case DEFAULT:
			glUseProgram(shader[DEFAULT]);
			break;
		case INT:
			glUseProgram(shader[INT]);
			break;
		case IF:
			glUseProgram(shader[IF]);
			break;
		case FUNC:
			glUseProgram(shader[FUNC]);
			break;
		}
    
   if (shadeMode>0)
   {
      int id;
      float time = 0.001*glutGet(GLUT_ELAPSED_TIME);
      id = glGetUniformLocation(shader[shadeMode],"time");
      if (id>=0) glUniform1f(id,time);
   }
   

	switch(object){
		case DINO:
			glPushMatrix();
			glScaled(zoom,zoom,zoom);
			glCallList(modelID[DINO]);
			glTranslated(-1.0, -1.0, 0.0);
			glCallList(modelID[DINO]);
			glTranslated(2.0, 2.0, 0.0);
			glCallList(modelID[DINO]);
			glTranslated(0.0, -2.0, 0.0);
			glCallList(modelID[DINO]);
			glTranslated(-2.0, 2.0, 0.0);
			glCallList(modelID[DINO]);
			glPopMatrix();
			break;
		case SPHERE:
			//Draw Bball
			glPushMatrix();
			glScaled(zoom,zoom,zoom);
			Sphere();
			glPopMatrix();
			break;
		case BUNNY:
			glPushMatrix();
			glScaled(zoom-1,zoom-1,zoom-1);
			glCallList(modelID[BUNNY]);
			glTranslated(-1.0, -1.0, -1.0);
			glCallList(modelID[BUNNY]);
			glTranslated(2.0, 2.0, 2.0);
			glCallList(modelID[BUNNY]);
			glTranslated(0.0, -2.0, 1.0);
			glCallList(modelID[BUNNY]);
			glTranslated(-2.0, 2.0, -3.0);
			glCallList(modelID[BUNNY]);
			glPopMatrix();
			break;
		case DILLO:
			glPushMatrix();
			glScaled(zoom,zoom,zoom);
			glCallList(modelID[DILLO]);
			glTranslated(-1.0, -1.0, -1.0);
			glCallList(modelID[DILLO]);
			glTranslated(2.0, 2.0, 2.0);
			glCallList(modelID[DILLO]);
			glTranslated(0.0, -2.0, 1.0);
			glCallList(modelID[DILLO]);
			glTranslated(-2.0, 2.0, -3.0);
			glCallList(modelID[DILLO]);
			glPopMatrix();
			break;
		}
    
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
   Print("Angle=%d,%d FPS: %d Shader Mode: %s",th,ph,FramesPerSecond(), shaderText[shadeMode]);
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
   if (ch == 27) exit(0);
   //  Reset view angle
   if (ch == 'x'){
      th = ph = 0;
      zoom = 2;
   }
   
   // Change shader mode
   if (ch == 'm' || ch == 'M') shadeMode = (shadeMode+1)%5;
   
   // Change object displayed
   if (ch == 'p' || ch == 'P') object = (object+1)%4;
    
   // Zoom
   if (ch == 'i') zoom += .1;
   if(ch == 'o')
       if(zoom > .2) zoom -= .1;
    
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
 *  GLUT calls this routine when the window is resized
 */
void idle()
{
   //  Elapsed time in seconds
   double t = glutGet(GLUT_ELAPSED_TIME)/1000.0;
   lth = fmod(90*t,360.0);
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
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
   glutInitWindowSize(1000,1000);
   glutCreateWindow("Assignment 4: Ethan Kreloff");
   //  Set callbackss
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutSpecialFunc(special);
   glutKeyboardFunc(key);
   glutIdleFunc(idle);
    
   //  Create Shader Prog
   shader[DEFAULT] = CreateShaderProg("default.vert","default.frag");
   shader[INT] = CreateShaderProg("int.vert","int.frag");
   shader[IF] = CreateShaderProg("if.vert","if.frag");
   shader[FUNC] = CreateShaderProg("func.vert","func.frag");
   
   //  Load object
   modelID[DINO] = LoadOBJ("tyra.obj");
   modelID[BUNNY] = LoadOBJ("bunny.obj");
   modelID[DILLO] = LoadOBJ("armadillo.obj");

   //  Pass control to GLUT so it can interact with the user
   glutMainLoop();
   return 0;
}
