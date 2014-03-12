//
//  Renderer for OpenGL ES 2.0
//

#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#include <cmath>
#include <iostream>
#include "RenderingEngine.h"

//
//  Snarf in shaders as character strings
//
#define STRINGIFY(S)  #S
#include "../Shaders/hw6.vert"
#include "../Shaders/hw6.frag"

//
//  Subclass generic renderer
//
class RenderingEngine2 : public RenderingEngine
{
public:
   RenderingEngine2();                      //  Constructor
   void Initialize(int width,int height);   //  Initialize
   void Display(float t);                   //  Display scene
private:
   float modelview[16];                                                  //  Modelview matrix
   GLuint CreateShader(const char* source, GLenum shaderType) const;     //  Create shader
   GLuint CreateProgram(const char* vertSrc, const char* fragSrc) const; //  Create program
   void ApplyOrtho(int width,int height) const;                          //  Set orthogonal projection
   void LoadIdentity();                                                  //  Set identity matrix
   void Rotate(float degrees,float x,float y,float z);                   //  Apply rotation
   void ApplyModelview() const;                                          //  Set modelview
   GLuint shader;                                                        //  Shader program
};

//
//  Convenience function to retrun new OpenGL ES 2.0 renderer
//
RenderingEngine* CreateRenderer2()
{
   return new RenderingEngine2();
}

#include "cube.h"

//
//  Constructor
//
RenderingEngine2::RenderingEngine2()
{
    // Create & bind the color buffer so that the caller can allocate its space.
    glGenRenderbuffers(1,&renderbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER,renderbuffer);
}

//
//  Initialize for OpenGL ES 2.0
void RenderingEngine2::Initialize(int width,int height)
{
   //  Create depth buffer
   GLuint Zbuffer;
   glGenRenderbuffers(1,&Zbuffer);
   glBindRenderbuffer(GL_RENDERBUFFER,Zbuffer);
   glRenderbufferStorage(GL_RENDERBUFFER,
                         GL_DEPTH_COMPONENT16,
                         width,
                         height);
   //  Create the color buffer
   GLuint Cbuffer;
   glGenFramebuffers(1,&Cbuffer);
   glBindFramebuffer(GL_FRAMEBUFFER,Cbuffer);
   //  Attach the depth and color buffers.
   glFramebufferRenderbuffer(GL_FRAMEBUFFER,
                             GL_COLOR_ATTACHMENT0,
                             GL_RENDERBUFFER,
                             Cbuffer);
   glFramebufferRenderbuffer(GL_FRAMEBUFFER,
                             GL_DEPTH_ATTACHMENT,
                             GL_RENDERBUFFER,
                             Zbuffer);
   //  Bind the color buffer for rendering.
   glBindRenderbuffer(GL_RENDERBUFFER,Cbuffer);

   //  Set viewport to entire window
   glViewport(0, 0, width, height);
   //  Compile and set shader
   shader = CreateProgram(SimpleVertexShader, SimpleFragmentShader);
   glUseProgram(shader);
   //  Set projection
   ApplyOrtho(width,height);
   //  Initialize orientation
   OnRotate(DeviceOrientationPortrait);
   currentAngle = desiredAngle;
}

//
//  Display the scene
//
void RenderingEngine2::Display(float t)
{
   //  Clear to grey
   glClearColor(0.5,0.5,0.5,1.0);
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   //  Set rotation angle
   LoadIdentity();
   Rotate(currentAngle,0,0,1);
   Rotate(15,1,0,0);
   Rotate(90*t,0,1,0);
   ApplyModelview();

   //  Set up 3D vertex array
   GLuint verts = glGetAttribLocation(shader,"XYZW");
   glEnableVertexAttribArray(verts);
   glVertexAttribPointer(verts,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),&Vertices[0].xyz[0]);
   
   //Normals
   GLuint norms = glGetAttribLocation(shader, "normal");
   glEnableVertexAttribArray(norms);
    glVertexAttribPointer(norms, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), &Vertices[0].normals[0]);
    
   //  Set up 4D color array
   GLuint color = glGetAttribLocation(shader,"RGBA");
   glEnableVertexAttribArray(color);
   glVertexAttribPointer(color,4,GL_FLOAT,GL_FALSE,sizeof(Vertex),&Vertices[0].rgba[0]);
   //  Draw all vertexes
   glEnable(GL_DEPTH_TEST);
   glDrawArrays(GL_TRIANGLES,0,sizeof(Vertices)/sizeof(Vertex));
   //  Disable vertex arrays
   glDisableVertexAttribArray(verts);
   glDisableVertexAttribArray(color);
}

//
//  Set projection matrix
//
void RenderingEngine2::ApplyOrtho(int width,int height) const
{
   //  Create orthogonal projection matrix
   float asp = width/(float)height;
   float dim = 2.5;
   float a = 1/(dim*asp);
   float b = 1/dim;
   float mat[16] =
   {
      a, 0,  0, 0,
      0, b,  0, 0,
      0, 0, -b, 0,
      0, 0,  0, 1
   };
   //  Set projection matrix in shader
   GLint id = glGetUniformLocation(shader,"Projection");
   if (id>=0) glUniformMatrix4fv(id,1,0,mat);
}

//
//  Set modelview matrix to I
void RenderingEngine2::LoadIdentity()
{
   float I[16] =
   {
      1, 0, 0, 0,
      0, 1, 0, 0,
      0, 0, 1, 0,
      0, 0, 0, 1
   };
   memcpy(modelview,I,sizeof(modelview));
}

//
//  Apply rotation to modelview matrix
//
void RenderingEngine2::Rotate(float deg,float X,float Y,float Z)
{
   //  Normalize axis
   float l = sqrt(X*X+Y*Y+Z*Z);
   if (l==0) return;
   float x = X/l;
   float y = Y/l;
   float z = Z/l;
   //  Calculate sin and cos
   float s = std::sin(deg*3.1415927/180);
   float c = std::cos(deg*3.1415927/180);
   float C = 1-c;
   //  Rotation matrix
   float rot[16] =
   {
      C*x*x+c   , C*x*y+z*s , C*z*x-y*s , 0 ,
      C*x*y-z*s , C*y*y+c   , C*y*z+x*s , 0 ,
      C*z*x+y*s , C*y*z-x*s , C*z*z+c   , 0 ,
           0    ,      0    ,      0    , 1 ,
   };
   //  Copy old matrix 
   float mv0[16];
   memcpy(mv0,modelview,sizeof(modelview));
   //  Multiply matrixes
   for (int i=0;i<4;i++)
      for (int j=0;j<4;j++)
         modelview[4*i+j] = mv0[j]*rot[4*i]+ mv0[4+j]*rot[4*i+1]+ mv0[8+j]*rot[4*i+2]+ mv0[12+j]*rot[4*i+3];
}

//
//  Set model view (rotation) matrix
//
void RenderingEngine2::ApplyModelview() const
{
   //  Set the modelview matrix in shader
   GLint id = glGetUniformLocation(shader,"Modelview");
   if (id>=0) glUniformMatrix4fv(id,1,0,modelview);
}

//
//  Create shader
//
GLuint RenderingEngine2::CreateShader(const char* source,GLenum type) const
{
   //  Compile shader
   GLuint shader = glCreateShader(type);
   glShaderSource(shader,1,&source,0);
   glCompileShader(shader);
   //  Check for errors
   GLint stat;
   glGetShaderiv(shader,GL_COMPILE_STATUS,&stat);
   if (!stat)
   {
      GLchar buf[8192];
      glGetShaderInfoLog(shader,sizeof(buf),0,buf);
      std::cout << buf;
      exit(1);
   }
   return shader;
}

//
//  Create shader program
//
GLuint RenderingEngine2::CreateProgram(const char* vertSrc,const char* fragSrc) const
{
   //  Compile shaders
   GLuint vert = CreateShader(vertSrc,GL_VERTEX_SHADER);
   GLuint frag = CreateShader(fragSrc,GL_FRAGMENT_SHADER);
   //  Link program
   GLuint prog = glCreateProgram();
   glAttachShader(prog,vert);
   glAttachShader(prog,frag);
   glLinkProgram(prog);
   //  Check for errors
   GLint stat;
   glGetProgramiv(prog,GL_LINK_STATUS,&stat);
   if (!stat)
   {
      GLchar buf[8192];
      glGetProgramInfoLog(prog,sizeof(buf),0,buf);
      std::cout << buf;
      exit(1);
   }
   return prog;
}
