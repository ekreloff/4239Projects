/* *******************************************************
 * Created By Ethan Kreloff March 15, 2014.
 * *******************************************************
 * Based off of code from CSCI 5239/4239 Advanced Computer
 * Graphics at the University of Colorado, Boulder.
 * *******************************************************
 * Calls glut and gl functions to draw particles that 
 * are then moved around by the vertex shader to simulate
 * snow. 
 * *******************************************************
 * hw9.c
 * ******************************************************/



/*
 *  Particle Shaders
 *  'a' to toggle axes
 *  '0' snaps angles to 0,0
 *  arrows to rotate the world
 *  PgUp/PgDn zooms in/out
 */
#include "CSCIx239.h"
#include "print.c"
#include "project.c"
#include "fatal.c"
#include "shader.c"
#include "elapsed.c"
#include "errcheck.c"
#include "fps.c"
#include "loadtexbmp.c"
#include "noise.c"

int axes=1;       //  Display axes
int mode=0;       //  Shader mode
int th=0;         //  Azimuth of view angle
int ph=0;         //  Elevation of view angle
int n;            //  Particle count
double asp=1;     //  Aspect ratio
double dim=3.0;   //  Size of world
#define MODE 1
int shader[MODE] = {0}; //  Shader programs
char* text[] = {"Windy Snow"};

//  Set up array indexes for program
#define VELOCITY_ARRAY   4
#define START_ARRAY 5
char* Name[] = {"","","","","Vel","Start",NULL};
//  Point arrays
#define N 75
float Vert[3*N*N];
float Color[3*N*N];
float Vel[3*N*N];
float Start[N*N];

/*
 *  Random numbers with range and offset
 */
static float frand(float rng,float off)
{
    return rand()*rng/RAND_MAX+off;
}

/*
 *  Initialize particles
 */
void InitPart(void)
{
    //  Array Pointers
    float* vert  = Vert;
    float* color = Color;
    float* vel   = Vel;
    float* start = Start;
    //  Loop over NxN patch
    int i,j;
    n = N;
    for (i=0;i<n;i++)
    for (j=0;j<n;j++)
    {
        //  Location x,y,z
        *vert++ = frand(5.0, 0.0);
        *vert++ = frand(-3.0, 3.5);
        *vert++ = frand(2.0, 0.0);
        //  Color r,g,b (0.5-1.0)
        *color++ = frand(0.5,0.8);
        *color++ = frand(0.5,0.8);
        *color++ = frand(0.5,0.8);
        //  Velocity
        *vel++ = frand( 2.0,-2.0);
        *vel++ = frand(-1.5,0.0);
        *vel++ = frand( 2.0,-2.0);
        //  Launch time
        *start++ = frand(5.0,0.0);
    }
}

/*
 *  Draw particles
 */
void DrawPart(void)
{
    //  Set particle size
    glPointSize(3);
    //  Point vertex location to local array Vert
    glVertexPointer(3,GL_FLOAT,0,Vert);
    //  Point color array to local array Color
    glColorPointer(3,GL_FLOAT,0,Color);
    //  Point attribute arrays to local arrays
    glVertexAttribPointer(VELOCITY_ARRAY,3,GL_FLOAT,GL_FALSE,0,Vel);
    glVertexAttribPointer(START_ARRAY,1,GL_FLOAT,GL_FALSE,0,Start);
    //  Enable arrays used by DrawArrays
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableVertexAttribArray(VELOCITY_ARRAY);
    glEnableVertexAttribArray(START_ARRAY);

    //  Draw arrays
    glDrawArrays(GL_POINTS,0,n*n);
 
    //  Disable arrays
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableVertexAttribArray(VELOCITY_ARRAY);
    glDisableVertexAttribArray(START_ARRAY);
}

/*
 *  OpenGL (GLUT) calls this routine to display the scene
 */
void display()
{
    int id;
    float time = 0.001*glutGet(GLUT_ELAPSED_TIME);
    const double len=2.0;  //  Length of axes
    
    //  Erase the window and the depth buffer
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
    //  Enable Z-buffering in OpenGL
    glEnable(GL_DEPTH_TEST);
    //  Undo previous transformations
    glLoadIdentity();
    //  Set eye position
    glRotatef(ph,1,0,0);
    glRotatef(th,0,1,0);
    
    //
    //  Draw scene
    //
    //  Select shader (0 => no shader)
    glUseProgram(shader[mode]);
    //  Set time
    id = glGetUniformLocation(shader[mode],"time");
    if (id>=0) glUniform1f(id,time);
    id = glGetUniformLocation(shader[mode],"random");
    if (id>=0) glUniform1f(id,rand());
    
    //  Draw the particles
    DrawPart();
    
    //  No shader for what follows
    glUseProgram(0);
    
    //  Draw axes - no lighting from here on
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
    //  Display parameters
    glWindowPos2i(5,5);
    Print("FPS=%d Dim=%.1f Mode=%s",
          FramesPerSecond(),dim,text[mode]);
    //  Render the scene and make it visible
    ErrCheck("display");
    glFlush();
    glutSwapBuffers();
}

/*
 *  GLUT calls this routine when the window is resized
 */
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
    else if (key == GLUT_KEY_PAGE_DOWN)
    dim += 0.1;
    //  PageDown key - decrease dim
    else if (key == GLUT_KEY_PAGE_UP && dim>1)
    dim -= 0.1;
    //  Keep angles to +/-360 degrees
    th %= 360;
    ph %= 360;
    //  Update projection
    Project(0,asp,dim);
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
    //  Cycle modes
    else if (ch == 'm')
    mode = (mode+1)%MODE;
    else if (ch == 'M')
    mode = (mode+MODE-1)%MODE;
    //  Initialize on mode chane
    //if (ch=='m' || ch=='M')  InitPart();
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
    Project(0,asp,dim);
}

//
//  Create Shader Program with Location Names
//
int CreateShaderProgLoc(char* VertFile,char* FragFile,char* Name[])
{
    int k;
    //  Create program
    int prog = glCreateProgram();
    //  Create and compile vertex shader
    if (VertFile) CreateShader(prog,GL_VERTEX_SHADER,VertFile);
    //  Create and compile fragment shader
    if (FragFile) CreateShader(prog,GL_FRAGMENT_SHADER,FragFile);
    //  Set names
    for (k=0;Name[k];k++)
    if (Name[k][0])
    glBindAttribLocation(prog,k,Name[k]);
    ErrCheck("CreateShaderProg");
    //  Link program
    glLinkProgram(prog);
    //  Check for errors
    PrintProgramLog(prog);
    //  Return name
    return prog;
}

/*
 *  Start up GLUT and tell it what to do
 */
int main(int argc,char* argv[])
{
    //  Initialize GLUT
    glutInit(&argc,argv);
    //  Request double buffered, true color window with Z buffering at 600x600
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE | GLUT_ALPHA);
    glutInitWindowSize(600,600);
    glutCreateWindow("Ethan Kreloff - Assignment 9");
    //  Set callbacks
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(special);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);
    //  Confetti Cannon needs no fragment shader, but adds Vel and Start
    shader[0] = CreateShaderProgLoc("shader1.vert",NULL,Name);

    InitPart();
    //  Pass control to GLUT so it can interact with the user
    ErrCheck("init");
    glutMainLoop();
    return 0;
}
