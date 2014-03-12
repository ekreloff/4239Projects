//
//  Renderer for OpenGL ES 1.1
//

#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>
#include "RenderingEngine.h"

//
//  Subclass generic renderer
//
class RenderingEngine1 : public RenderingEngine
{
public:
   RenderingEngine1();                      //  Constructor
   void Initialize(int width,int height);   //  Initialize
   void Display(float t);                   //  Display scene
};

//
//  Convenience function to return new OpenGL ES 1.1 renderer
//
RenderingEngine* CreateRenderer1()
{
   return new RenderingEngine1();
}

#include "cube.h"

//
//  Constructor
//
RenderingEngine1::RenderingEngine1()
{
    // Create & bind the color buffer so that the caller can allocate its space.
    glGenRenderbuffersOES(1,&renderbuffer);
    glBindRenderbufferOES(GL_RENDERBUFFER_OES,renderbuffer);
}

//
//  Initialize for OpenGL ES 1.1
//
void RenderingEngine1::Initialize(int width,int height)
{
   //  Create depth buffer
   GLuint Zbuffer;
   glGenRenderbuffersOES(1,&Zbuffer);
   glBindRenderbufferOES(GL_RENDERBUFFER_OES,Zbuffer);
   glRenderbufferStorageOES(GL_RENDERBUFFER_OES,
                            GL_DEPTH_COMPONENT16_OES,
                            width,
                            height);
   //  Create the color buffer
   GLuint Cbuffer;
   glGenFramebuffersOES(1,&Cbuffer);
   glBindFramebufferOES(GL_FRAMEBUFFER_OES,Cbuffer);
   //  Attach the depth and color buffers.
   glFramebufferRenderbufferOES(GL_FRAMEBUFFER_OES,
                                GL_COLOR_ATTACHMENT0_OES,
                                GL_RENDERBUFFER_OES,
                                Cbuffer);
   glFramebufferRenderbufferOES(GL_FRAMEBUFFER_OES,
                                GL_DEPTH_ATTACHMENT_OES,
                                GL_RENDERBUFFER_OES,
                                Zbuffer);
   //  Bind the color buffer for rendering.
   glBindRenderbufferOES(GL_RENDERBUFFER_OES,Cbuffer);

   //  Set viewport to entire window
   glViewport(0, 0, width, height);

   //  Set projection
   glMatrixMode(GL_PROJECTION);
   float asp = width/(float)height;
   float dim = 2.5;
   glOrthof(-dim*asp,+dim*asp,-dim,+dim,-dim,+dim);
   //  Set model view mode
   glMatrixMode(GL_MODELVIEW);

   // Initialize orientation
   OnRotate(DeviceOrientationPortrait);
   currentAngle = desiredAngle;
}

//
//  Display the scene
//
void RenderingEngine1::Display(float t)
{
   //  Clear to grey
   glClearColor(0.5,0.5,0.5,1.0);
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   //  Set view angle
   glLoadIdentity();
   glRotatef(currentAngle,0,0,1);
   glRotatef(15,1,0,0);
   glRotatef(90*t,0,1,0);

   //  Set up 3D vertex array
   glEnableClientState(GL_VERTEX_ARRAY);
   glVertexPointer(3,GL_FLOAT,sizeof(Vertex),&Vertices[0].xyz[0]);
   //  Set up 4D color array
   glEnableClientState(GL_COLOR_ARRAY);
   glColorPointer(4,GL_FLOAT,sizeof(Vertex),&Vertices[0].rgba[0]);
   //  Draw all vertexes
   glEnable(GL_DEPTH_TEST);
   glDrawArrays(GL_TRIANGLES,0,sizeof(Vertices)/sizeof(Vertex));
   //  Disable vertex arrays   
   glDisableClientState(GL_VERTEX_ARRAY);
   glDisableClientState(GL_COLOR_ARRAY);
}
