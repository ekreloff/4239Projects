/* *******************************************************
 * Created By Ethan Kreloff February 2, 2014.
 * *******************************************************
 * Based off of code from CSCI 5239/4239 Advanced Computer
 * Graphics at the University of Colorado, Boulder.
 * *******************************************************
 * Calls glut and gl functions to a sphere
 * *******************************************************
 * hw3.c
 * ******************************************************/

// OpenGL 2.0 is deprecated in Mavericks
#ifdef __APPLE__
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif

#include "CSCIx239.h"
#include "print.c"
#include "project.c"
#include "fatal.c"
#include "shader.c"
#include "loadtexbmp.c"
#include "noise.c"
#include "elapsed.c"
#include "errcheck.c"
#include "fps.c"
#include "object.c"


#define MODE 3
#define TEXTURES 3


/*
 *  Global variables 
 */


int shadeMode = 0; //Shader Mode
int th=0;         //  Azimuth of view angle
int ph=0;         //  Elevation of view angle
int fov=55;       //  Field of view (for perspective)
int axes = 0;     //  Display axes
double asp=1.0;     //  Aspect ratio
double dim=5.0;   //  Size of world
double zoom = .75;  //Scaling factor
int woodShader = 0; //Shaders
int bumpShader = 0;
int texture[TEXTURES]; //Textures

// Lighting Variables
int lth = 90; // Lighting Azimuth
int YLight = 5; // Y component of light



/*
 *  Prototypes
 */
static void Vertex(int th,int ph);
void Sphere();

void FloorBounds();

void Floor();

void Hoop(double x, double y, double z, double yrot);




/*
 *  OpenGL (GLUT) calls this routine to display the scene
 */
void display()
{
   
   //  Light position and colors
//   float Emission[]  = {0.0,0.0,0.0,1.0};
//   float Ambient[]   = {0.3,0.3,0.3,1.0};
//   float Diffuse[]   = {1.0,1.0,1.0,1.0};
//   float Specular[]  = {1.0,1.0,1.0,1.0};
//   float Position[]  = {2*Cos(lth),YLight,2*Sin(lth),1.0};
//   float Shinyness[] = {36};
    
//    GLfloat ambient_light[] =
//    GLfloat diffuse_light[] =
//    GLfloat specular_light[] =
//    GLfloat position_light[] = { 0.0f, 0.0f, -1.0f, 0.0f };

    float Emission[]  = {0.0,0.0,0.0,1.0};
    float Ambient[]   = { 0.2f, 0.2f, 0.2f, 1.0f };
    float Diffuse[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
    float Specular[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
    float Position[]  = {2*Cos(lth),YLight,2*Sin(lth),1.0};
    float Shinyness[] = {.6};
    
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
    gluLookAt(Ex,Ey,Ez , 0.0,0.0,0.0 , 0,Cos(ph),0);
    
    
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
    
    //  Texture binding
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,texture[0]);
    
    int id;
    glUseProgram(woodShader);
    id = glGetUniformLocation(woodShader,"Noise3D");
    if (id>=0) glUniform1i(id,1);
    
    id = glGetUniformLocation(woodShader,"CourtTex0");
    if (id>=0) glUniform1i(id,0);
    
    glPushMatrix();
    glScaled(zoom,zoom,zoom);
    glUseProgram(woodShader);
    Floor();
    FloorBounds();
    glPopMatrix();

    
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D,texture[1]);
    
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D,texture[2]);
    
    

    glUseProgram(bumpShader);
    id = glGetUniformLocation(bumpShader,"tex1");
    if (id>=0) glUniform1i(id,2);
    
    id = glGetUniformLocation(bumpShader,"tex0");
    if (id>=0) glUniform1i(id,3);
    
    
    
 
    //Draw Bball
    glPushMatrix();
    glScaled(zoom,zoom,zoom);
    glUseProgram(bumpShader);
    Sphere();
    glUseProgram(0);
    Hoop(-24.0, -.775, 3.0, 90.0);
    Hoop(25.1, -.775, 1.2, -90.0);
    //  No shader for what follows
    glUseProgram(0);
    glPopMatrix();
    
    
   
    
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
    /*Print("RingFreq=%.4f    LightGrains=%.4f    DarkGrains=%.4f\
             GrainThreshold=%.4f    Noisiness=%.4f    GrainScale=%.4f\
             Scale=%.4f    NoiseScale=%.4f,%.4f,%.4f",RingFreq,LightGrains,DarkGrains,GrainThreshold,Noisiness,GrainScale,Scale,NoiseScale[0],NoiseScale[1],NoiseScale[2]);*/
   //  Render the scene and make it visible
   glFlush();
   glutSwapBuffers();
}

void idle()
{
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
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
      th = ph = 0;
      zoom = 1;
   }
   //  Change field of view angle
   if (ch == '9' && ch>1)
      fov--;
   if (ch == '0' && ch<179)
      fov++;
   if (ch == 'm' || ch == 'M')
      shadeMode = (shadeMode+1)%MODE;
    
      //  Light elevation
   if (ch == '1') YLight += 0.5;
   if (ch == '2') YLight -= 0.5;
   //  Light position
   if (ch == '[') lth--;
   if (ch == ']') lth++;
   
    
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
    int n;
   //  Initialize GLUT
   glutInit(&argc,argv);
   //  Request double buffered, true color window with Z buffering at 600x600
   glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
   glutInitWindowSize(1700,1100);
   glutCreateWindow("Final Project: Ethan Kreloff");
   //  Set callbacks
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutSpecialFunc(special);
   glutKeyboardFunc(key);
    
    glGetIntegerv(GL_MAX_TEXTURE_UNITS,&n);
    if (n<4) Fatal("Insufficient texture Units %d\n",n);
    
   //  Load textures
   glActiveTexture(GL_TEXTURE0);
   texture[0]  = LoadTexBMP("pepsicenter.bmp");
    
   glActiveTexture(GL_TEXTURE2);
   texture[1] = LoadTexBMP("normal.bmp");
    
   glActiveTexture(GL_TEXTURE3);
   texture[2]  = LoadTexBMP("leather.bmp");
    
   //  Create Shader Prog
   woodShader = CreateShaderProg("noise.vert","wood.frag");
   bumpShader = CreateShaderProg("bump.vert","bump.frag");
    

   //  Load random texture
   CreateNoise3D(GL_TEXTURE1);

   //  Pass control to GLUT so it can interact with the user
   glutMainLoop();
   return 0;
}



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
    glPushMatrix();
    glScaled(0.25, 0.25, 0.25);
    //glTranslated(-50, 12, 0);
    for (ph=-90;ph<90;ph+=5)
    {
        glBegin(GL_QUAD_STRIP);
        glScaled(0.1, 0.1, 0.1);
        for (th=0;th<=360;th+=5)
        {
            Vertex(th,ph);
            Vertex(th,ph+5);
        }
        glEnd();
    }
    glPopMatrix();
}

void FloorBounds(){
    glColor3f(0.027,0.112,0.208);
    glBegin(GL_QUADS);
    glNormal3d(0.0, 1.0, 0.0);
    glVertex3d(25.62, -0.499, -13.0);
    glVertex3d(25.62, -0.499, -10.47);
    glVertex3d(-24.5, -0.499, -10.47);
    glVertex3d(-24.5, -0.499, -13.0);
    glEnd();
    
    glBegin(GL_QUADS);
    glNormal3d(0.0, 1.0, 0.0);
    glVertex3d(25.62, -0.499, 17.0);
    glVertex3d(25.62, -0.499, 14.42);
    glVertex3d(-24.5, -0.499, 14.42);
    glVertex3d(-24.5, -0.499, 17.0);
    glEnd();
    
    glBegin(GL_QUADS);
    glNormal3d(0.0, 1.0, 0.0);
    glVertex3d(-24.5, -0.499, -13.0);
    glVertex3d(-28.5, -0.499, -13.0);
    glVertex3d(-28.5, -0.499, 17.0);
    glVertex3d(-24.5, -0.499, 17.0);
    glEnd();
    
    glBegin(GL_QUADS);
    glNormal3d(0.0, 1.0, 0.0);
    glVertex3d(25.62, -0.499, -13.0);
    glVertex3d(25.62, -0.499, 17.0);
    glVertex3d(29.62, -0.499, 17.0);
    glVertex3d(29.62, -0.499, -13.0);
    glEnd();
}

void Floor(){
    double i, j;
    int offset = 0;
    for(i = 1; i <= 50; i += 2.005){
        for (j = 1; j <= 28; j += 0.126) {
            glColor3f(.5,.5,.5);
            glBegin(GL_QUADS);
            glNormal3d(0.0, 1.0, 0.0);
            double off;
            if(offset)off = 1.0;
            else off = 0.0;
            glTexCoord2d(0,1); glVertex3d(-23.5+i, -0.5, -12.5+j+off);
            glTexCoord2d(0,0); glVertex3d(-23.5+i, -0.5, -12.38+j+off);
            glTexCoord2d(1,0); glVertex3d(-25.5+i, -0.5, -12.38+j+off);
            glTexCoord2d(1,1); glVertex3d(-25.5+i, -0.5, -12.5+j+off);
            glEnd();
            offset = !offset;
        }
    }
}

void Hoop(double x, double y, double z, double yrot){
    glPushMatrix();
    glTranslated(x, y, z);
    glRotated(yrot, 0.0, 1.0, 0.0);
    glScaled(1.5, 1.3, 1.5);
    
    glColor3f(.8,.8,.8);
    //Backbaord front
    glBegin(GL_QUADS);
    glNormal3d(0.0, 0.0, 1.0);
    glVertex3d(-0.5, 5.0, 0.0);
    glVertex3d(-0.5, 3.65, 0.0);
    glVertex3d(1.5, 3.65, 0.0);
    glVertex3d(1.5, 5.0, 0.0);
    glEnd();
    //Backboard sides
    glBegin(GL_QUADS);
    glNormal3d(-1.0, 0.0, 0.0);
    glVertex3d(-0.5, 5.0, 0.0);
    glVertex3d(-0.5, 5.0, -0.15);
    glVertex3d(-0.5, 3.65, -0.15);
    glVertex3d(-0.5, 3.65, 0.0);
    glEnd();
    
    glBegin(GL_QUADS);
    glNormal3d(1.0, 0.0, 0.0);
    glVertex3d(1.5, 5.0, 0.0);
    glVertex3d(1.5, 3.65, 0.0);
    glVertex3d(1.5, 3.65, -0.15);
    glVertex3d(1.5, 5.0, -0.15);
    glEnd();
    
    glBegin(GL_QUADS);
    glNormal3d(0.0, 1.0, 0.0);
    glVertex3d(1.5, 5.0, 0.0);
    glVertex3d(1.5, 5.0, -0.15);
    glVertex3d(-0.5, 5.0, -0.15);
    glVertex3d(-0.5, 5.0, 0.0);
    glEnd();
    
    glBegin(GL_QUADS);
    glNormal3d(0.0, -1.0, 0.0);
    glVertex3d(1.5, 3.65, 0.0);
    glVertex3d(1.5, 3.65, -0.15);
    glVertex3d(-0.5, 3.65, -0.15);
    glVertex3d(-0.5, 3.65, 0.0);
    glEnd();
    
    //backboard back
    glBegin(GL_QUADS);
    glNormal3d(0.0, 0.0, -1.0);
    glVertex3d(-0.5, 5.0, -0.15);
    glVertex3d(-0.5, 3.65, -0.15);
    glVertex3d(1.5, 3.65, -0.15);
    glVertex3d(1.5, 5.0, -0.15);
    glEnd();
    
    //Post
    glColor3f(0.1,0.1,0.1);
    glBegin(GL_QUADS);
    glNormal3d(-1.0, 0.0, 0.0);
    glVertex3d(0.35, 3.8, -0.15);
    glVertex3d(0.35, 4.05, -0.15);
    glVertex3d(0.35, 4.05, -0.6);
    glVertex3d(0.35, 3.8, -0.6);
    glEnd();
    
    glBegin(GL_QUADS);
    glNormal3d(1.0, 0.0, 0.0);
    glVertex3d(0.65, 3.8, -0.15);
    glVertex3d(0.65, 4.05, -0.15);
    glVertex3d(0.65, 4.05, -0.6);
    glVertex3d(0.65, 3.8, -0.6);
    glEnd();
    
    glBegin(GL_QUADS);
    glNormal3d(0.0, -1.0, 0.0);
    glVertex3d(0.65, 3.8, -0.15);
    glVertex3d(0.65, 3.8, -0.6);
    glVertex3d(0.35, 3.8, -0.6);
    glVertex3d(0.35, 3.8, -0.15);
    glEnd();
    
    glBegin(GL_QUADS);
    glNormal3d(0.0, 1.0, 0.0);
    glVertex3d(0.65, 4.05, -0.15);
    glVertex3d(0.65, 4.05, -0.9);
    glVertex3d(0.35, 4.05, -0.9);
    glVertex3d(0.35, 4.05, -0.15);
    glEnd();
    
    glBegin(GL_QUADS);
    glNormal3d(0.0, 0.0, -1.0);
    glVertex3d(0.65, 4.05, -0.9);
    glVertex3d(0.65, .275, -0.9);
    glVertex3d(0.35, .275, -0.9);
    glVertex3d(0.35, 4.05, -0.9);
    glEnd();
    
    glBegin(GL_QUADS);
    glNormal3d(1.0, 0.0, 0.0);
    glVertex3d(0.65, 4.05, -0.9);
    glVertex3d(0.65, 4.05, -0.6);
    glVertex3d(0.65, .275, -0.6);
    glVertex3d(0.65, .275, -0.9);
    glEnd();
    
    glBegin(GL_QUADS);
    glNormal3d(-1.0, 0.0, 0.0);
    glVertex3d(0.35, 4.05, -0.9);
    glVertex3d(0.35, .275, -0.9);
    glVertex3d(0.35, .275, -0.6);
    glVertex3d(0.35, 4.05, -0.6);
    glEnd();
    
    glBegin(GL_QUADS);
    glNormal3d(0.0, 0.0, 1.0);
    glVertex3d(0.35, 4.05, -0.6);
    glVertex3d(0.35, .275, -0.6);
    glVertex3d(0.65, .275, -0.6);
    glVertex3d(0.65, 4.05, -0.6);
    glEnd();
    
    glPopMatrix();
}


/*
 void Floortest(){
 
 glColor3f(.5,.5,.5);
 glBegin(GL_QUADS);
 glNormal3d(0.0, 1.0, 0.0);
 glVertex3d(-23.5, -0.5, -12.5);
 glVertex3d(-23.5, -0.5, -1.38);
 glVertex3d(-2.5, -0.5, -1.38);
 glVertex3d(-2.5, -0.5, -12.5);
 glEnd();
 
 
 }
 
 void Floor2(){
 double i, j;
 int offset = 0;
 for(i = 1; i <= 50; i += //2.005// 3.0){
 for (j = 1; j <= 28; j += //0.127// .5) {
 glColor3f(.5,.5,.5);
 glBegin(GL_QUADS);
 glNormal3d(0.0, 1.0, 0.0);
 double off;
 if(offset)off = 1.0;
 else off = 0.0;
 glVertex3d(-23.5+i, -0.5, -12.5+j+off);
 glVertex3d(-23.5+i, -0.5, -12.38+j+off);
 glVertex3d(-25.5+i, -0.5, -12.38+j+off);
 glVertex3d(-25.5+i, -0.5, -12.5+j+off);
 glEnd();
 offset = !offset;
 }
 }
 
 }*/
