#import "GLView.h"
#import <OpenGLES/ES2/gl.h> // <-- for GL_RENDERBUFFER only

//  Switch to force usage of OpenGL ES 1.1
const bool ForceES1 = false;

@implementation GLView

//
//  Reimplement method to return an OpenGL friendly layer
//
+ (Class) layerClass
{
   return [CAEAGLLayer class];
}

//
//  Initialize GLView with frame  (constructor)
//
- (id) initWithFrame: (CGRect) frame
{
   //  Initialize parent
   if (self = [super initWithFrame:frame])
   {
      //  Get layer
      CAEAGLLayer* eaglLayer = (CAEAGLLayer*) super.layer;
     //  Transparency will be handled by OpenGL
      eaglLayer.opaque = YES;

      //  First try to initialize OpenGL ES 2.0 API
      EAGLRenderingAPI api = kEAGLRenderingAPIOpenGLES2;
      context = [[EAGLContext alloc] initWithAPI:api];

      //  On failure or if forced OpenGL ES 1.1, switch to OpenGL ES 1.1 API 
      if (!context || ForceES1)
      {
         api = kEAGLRenderingAPIOpenGLES1;
         context = [[EAGLContext alloc] initWithAPI:api];
      }

      //  Disaster!!! Failed to initialize any OpenGL ES API
      if (!context || ![EAGLContext setCurrentContext:context])
      {
         [self release];
         return nil;
      }

      //  Create rendering engine for OpenGL ES 1.1
      if (api == kEAGLRenderingAPIOpenGLES1)
      {
         NSLog(@"Using OpenGL ES 1.1");
         renderer = CreateRenderer1();
      }
      //  Create rendering engine for OpenGL ES 2.0
      else
      {
         NSLog(@"Using OpenGL ES 2.0");
         renderer = CreateRenderer2();
      }

      //  Attach OpenGL render buffer to layer
      [context renderbufferStorage:GL_RENDERBUFFER fromDrawable:eaglLayer];

      //  Initialize the rendering engine sized to frame
      //  The CG macros are from the Core Graphics framework
      renderer->Initialize(CGRectGetWidth(frame),CGRectGetHeight(frame));

     //  Draw the scene the first time
      [self drawView: nil];

      //  Remember current time
      t0 = CACurrentMediaTime();

      CADisplayLink* displayLink;
      displayLink = [CADisplayLink displayLinkWithTarget:self selector:@selector(drawView:)];
     
      [displayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];

      [[UIDevice currentDevice] beginGeneratingDeviceOrientationNotifications];
     
      [[NSNotificationCenter defaultCenter]
         addObserver:self
         selector:@selector(didRotate:)
         name:UIDeviceOrientationDidChangeNotification
         object:nil];
   }
   return self;
}

//
//  Receive device rotation notification
//
- (void) didRotate: (NSNotification*) notification
{
   //  Retrieve orientation
   UIDeviceOrientation orientation = [[UIDevice currentDevice] orientation];
   //  Set rotation for renderer
   renderer->OnRotate((DeviceOrientation)orientation);
   //  Redisplay
   [self drawView: nil];
}

//
//  Redisplay
//
- (void) drawView: (CADisplayLink*) displayLink
{
   if (displayLink != nil)
   {
      //  Get elapsed time
      float dt = displayLink.timestamp - t0;
      //  Remember current time
      t0 = displayLink.timestamp;
      //  Update animation in renderer
      renderer->UpdateAnimation(dt);
   }

   //  Redisplay scene
   renderer->Display(t0);
   //  Flush render buffer to screen
   [context presentRenderbuffer:GL_RENDERBUFFER];
}

@end
