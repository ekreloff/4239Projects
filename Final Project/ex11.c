/*
 *  Image Processing
 *
 *  Based on the examples in OpenGL SuperBible Chapter 17
 *
 *  'm' to switch filters
 *  'n' to change number of passes
 *  'p' to switch projections
 *  's' to start/stop light
 *  'l' light on/off
 *  'a' to toggle axes
 *  '0' snaps angles to 0,0
 *  arrows to rotate the world
 *  PgUp/PgDn zooms in/out
 *  -/+    change light elevation
 */
#include "CSCIx239.h"
int axes=1;         //  Display axes
int mode=0;         //  Shader mode
int move=1;         //  Move light
int proj=1;         //  Projection type
int light=1;        //  Lighting
int th=0;           //  Azimuth of view angle
int ph=0;           //  Elevation of view angle
int fov=55;         //  Field of view (for perspective)
double asp=1;       //  Aspect ratio
double dim=3.0;     //  Size of world
int zh=90;          //  Light azimuth
float Ylight=2;     //  Light elevation
int cruiser;        //  Cruiser model
int tyra;           //  Tyrannosaurus model
int crate;          //  Crate texture
int tex=0;          //  Show crate texture
unsigned int img;   //  Image texture
int W,H;            //  Texture dimensions
int N=1;            //  Texture passes
int MaxTexSize;     //  Maximum texture size
float dX,dY;        //  Image pixel offset
#define MODE 9
int shader[MODE] = {0}; //  Shader programs
char* text[] = {"No Shader","Copy","Sharpen","Blur","Erosion","Dilation","Laplacian Edge Detection","Prewitt Edge Detection","Sobel Edge Detection"};

/*
 *  Draw a cube
 */
static void Cube(void)
{
   if (tex) glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D,crate);
   //  Front
   glColor3f(1,0,0);
   glBegin(GL_QUADS);
   glNormal3f( 0, 0,+1);
   glTexCoord2f(0,0); glVertex3f(-1,-1,+1);
   glTexCoord2f(1,0); glVertex3f(+1,-1,+1);
   glTexCoord2f(1,1); glVertex3f(+1,+1,+1);
   glTexCoord2f(0,1); glVertex3f(-1,+1,+1);
   glEnd();
   //  Back
   glColor3f(0,0,1);
   glBegin(GL_QUADS);
   glNormal3f( 0, 0,-1);
   glTexCoord2f(0,0); glVertex3f(+1,-1,-1);
   glTexCoord2f(1,0); glVertex3f(-1,-1,-1);
   glTexCoord2f(1,1); glVertex3f(-1,+1,-1);
   glTexCoord2f(0,1); glVertex3f(+1,+1,-1);
   glEnd();
   //  Right
   glColor3f(1,1,0);
   glBegin(GL_QUADS);
   glNormal3f(+1, 0, 0);
   glTexCoord2f(0,0); glVertex3f(+1,-1,+1);
   glTexCoord2f(1,0); glVertex3f(+1,-1,-1);
   glTexCoord2f(1,1); glVertex3f(+1,+1,-1);
   glTexCoord2f(0,1); glVertex3f(+1,+1,+1);
   glEnd();
   //  Left
   glColor3f(0,1,0);
   glBegin(GL_QUADS);
   glNormal3f(-1, 0, 0);
   glTexCoord2f(0,0); glVertex3f(-1,-1,-1);
   glTexCoord2f(1,0); glVertex3f(-1,-1,+1);
   glTexCoord2f(1,1); glVertex3f(-1,+1,+1);
   glTexCoord2f(0,1); glVertex3f(-1,+1,-1);
   glEnd();
   //  Top
   glColor3f(0,1,1);
   glBegin(GL_QUADS);
   glNormal3f( 0,+1, 0);
   glTexCoord2f(0,0); glVertex3f(-1,+1,+1);
   glTexCoord2f(1,0); glVertex3f(+1,+1,+1);
   glTexCoord2f(1,1); glVertex3f(+1,+1,-1);
   glTexCoord2f(0,1); glVertex3f(-1,+1,-1);
   glEnd();
   //  Bottom
   glColor3f(1,0,1);
   glBegin(GL_QUADS);
   glNormal3f( 0,-1, 0);
   glTexCoord2f(0,0); glVertex3f(-1,-1,-1);
   glTexCoord2f(1,0); glVertex3f(+1,-1,-1);
   glTexCoord2f(1,1); glVertex3f(+1,-1,+1);
   glTexCoord2f(0,1); glVertex3f(-1,-1,+1);
   glEnd();
   if (tex) glDisable(GL_TEXTURE_2D);
}

/*
 *  OpenGL (GLUT) calls this routine to display the scene
 */
void display()
{
   int k;
   const double len=2.0;  //  Length of axes
   //  Light position and colors
   float Emission[]  = {0.0,0.0,0.0,1.0};
   float Ambient[]   = {0.3,0.3,0.3,1.0};
   float Diffuse[]   = {1.0,1.0,1.0,1.0};
   float Specular[]  = {1.0,1.0,1.0,1.0};
   float Position[]  = {2*Cos(zh),Ylight,2*Sin(zh),1.0};
   float Shinyness[] = {16};

   //  Erase the window and the depth buffer
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

   //  Enable Z-buffering in OpenGL
   glEnable(GL_DEPTH_TEST);
   //  Undo previous transformations
   glLoadIdentity();
   //  Reproject
   Project(proj?fov:0,asp,dim);
   //  Perspective - set eye position
   if (proj)
   {
      double Ex = -2*dim*Sin(th)*Cos(ph);
      double Ey = +2*dim        *Sin(ph);
      double Ez = +2*dim*Cos(th)*Cos(ph);
      gluLookAt(Ex,Ey,Ez , 0,0,0 , 0,Cos(ph),0);
   }
   //  Orthogonal - set world orientation
   else
   {
      glRotatef(ph,1,0,0);
      glRotatef(th,0,1,0);
   }

   if (light)
   {
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
   }

   //  Draw the cruiser
   glColor3f(1,1,1);
   glPushMatrix();
   glTranslated(1,1,0);
   glCallList(cruiser);
   glPopMatrix();
   //  Draw the tyrannosaurus
   glColor3f(0.54,0.27,0.07);
   glPushMatrix();
   glTranslated(1,-1,0);
   glScaled(0.6,0.6,0.6);
   glRotated(180,0,1,0);
   glCallList(tyra);
   glPopMatrix();
   //  Draw teapot
   glPushMatrix();
   glTranslated(-1,-1,0);
   glColor3f(1,1,0);
   glutSolidTeapot(0.5);
   glPopMatrix();
   //  Draw cube
   glPushMatrix();
   glTranslated(-1,1,0);
   glScaled(0.5,0.5,0.5);
   Cube();
   glPopMatrix();

   //  Draw axes - no lighting from here on
   glDisable(GL_LIGHTING);
   glColor3f(1,1,1);
   if (axes)
   {
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

   //
   //  Process images
   //
   if (mode>0)
   {
      //  Set shader
      glUseProgram(shader[mode]);

      //  Set offsets
      int id = glGetUniformLocation(shader[mode],"dX");
      if (id>=0) glUniform1f(id,dX);
      id = glGetUniformLocation(shader[mode],"dY");
      if (id>=0) glUniform1f(id,dY);

      //  Disable depth
      glDisable(GL_DEPTH_TEST);

      //  Indentity projections
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();

      //  Shader passes
      for (k=0;k<N;k++)
      {
         glBindTexture(GL_TEXTURE_2D,img);
         //  Copy original scene to texture
         glCopyTexImage2D(GL_TEXTURE_2D,0,GL_RGBA8,0,0,W,H,0);

         //  Redraw the texture
         glClear(GL_COLOR_BUFFER_BIT);
         glEnable(GL_TEXTURE_2D);
         glBegin(GL_QUADS);
         glTexCoord2f(0,0); glVertex2f(-1,-1);
         glTexCoord2f(0,1); glVertex2f(-1,+1);
         glTexCoord2f(1,1); glVertex2f(+1,+1);
         glTexCoord2f(1,0); glVertex2f(+1,-1);
         glEnd();
         glDisable(GL_TEXTURE_2D);
      }

      //  Shader off
      glUseProgram(0);
   }

   //  Display parameters
   glWindowPos2i(5,5);
   Print("FPS=%d Dim=%.1f Projection=%s Mode=%s Passes=%d",
     FramesPerSecond(),dim,proj?"Perpective":"Orthogonal",text[mode],N);
   //  Render the scene and make it visible
   ErrCheck("display");
   glFlush();
   glutSwapBuffers();
}

/*
 *  GLUT calls this routine when idle
 */
void idle()
{
   //  Elapsed time in seconds
   double t = glutGet(GLUT_ELAPSED_TIME)/1000.0;
   if (move) zh = fmod(90*t,360.0);
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
   else if (key == GLUT_KEY_PAGE_DOWN)
      dim += 0.1;
   //  PageDown key - decrease dim
   else if (key == GLUT_KEY_PAGE_UP && dim>1)
      dim -= 0.1;
   //  Keep angles to +/-360 degrees
   th %= 360;
   ph %= 360;
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
   else if (ch == '0')
      th = ph = 0;
   //  Toggle axes
   else if (ch == 'a' || ch == 'A')
      axes = 1-axes;
   //  Toggle projection type
   else if (ch == 'p' || ch == 'P')
      proj = 1-proj;
   //  Toggle light
   else if (ch == 'l' || ch == 'L')
      light = 1-light;
   //  Toggle light movement
   else if (ch == 's' || ch == 'S')
      move = 1-move;
   //  Toggle crate texture
   else if (ch == 't' || ch == 'T')
      tex = 1-tex;
   //  Passes
   else if (ch == 'N' && N>1)
      N--;
   else if (ch == 'n')
      N++;
   //  Cycle modes
   else if (ch == 'm')
      mode = (mode+1)%MODE;
   else if (ch == 'M')
      mode = (mode+MODE-1)%MODE;
   //  Light elevation
   else if (ch == '+')
      Ylight += 0.1;
   else if (ch == '-')
      Ylight -= 0.1;
   //  Light position
   else if (ch == '[')
      zh--;
   else if (ch == ']')
      zh++;
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

   //  Set size of texture
   W = width;
   H = height;
   if (W>MaxTexSize) W = MaxTexSize;
   if (H>MaxTexSize) H = MaxTexSize;
   //  Set texture offsets for kernel
   dX = 1.0/W;
   dY = 1.0/H;
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
   glutCreateWindow("Image Processing");
#ifdef USEGLEW
   //  Initialize GLEW
   if (glewInit()!=GLEW_OK) Fatal("Error initializing GLEW\n");
   if (!GLEW_VERSION_2_0) Fatal("OpenGL 2.0 not supported\n");
#endif
   //  Set callbacks
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutSpecialFunc(special);
   glutKeyboardFunc(key);
   glutIdleFunc(idle);
   //  Maximum texture size
   glGetIntegerv(GL_MAX_TEXTURE_SIZE,&MaxTexSize);
   //  Background color
   glClearColor(0.3,0.3,0.3,1.0);
   //  Load crate texture
   crate = LoadTexBMP("crate.bmp");
   //  Load object
   cruiser = LoadOBJ("cruiser.obj");
   tyra    = LoadOBJ("tyra.obj");
   //  Create Shader Programs
   shader[1] = CreateShaderProg(NULL,"copy.frag");
   shader[2] = CreateShaderProg(NULL,"sharpen.frag");
   shader[3] = CreateShaderProg(NULL,"blur.frag");
   shader[4] = CreateShaderProg(NULL,"erosion.frag");
   shader[5] = CreateShaderProg(NULL,"dilation.frag");
   shader[6] = CreateShaderProg(NULL,"laplacian.frag");
   shader[7] = CreateShaderProg(NULL,"prewitt.frag");
   shader[8] = CreateShaderProg(NULL,"sobel.frag");
   //  Image texture
   glGenTextures(1,&img);
   glBindTexture(GL_TEXTURE_2D,img);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
   //  Pass control to GLUT so it can interact with the user
   ErrCheck("init");
   glutMainLoop();
   return 0;
}
