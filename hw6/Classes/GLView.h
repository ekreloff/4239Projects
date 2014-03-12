//
//  Class to display OpenGL ES
//  Derived from UIView to get display
//  and controls
//

#import "RenderingEngine.h"
#import <QuartzCore/QuartzCore.h>

@interface GLView : UIView
{
@private
   EAGLContext*     context;   //  Access to EGL
   RenderingEngine* renderer;  //  Pointer to C++ Renderer class
   float            t0;        //  Previous time for animations
}

- (void) drawView:  (CADisplayLink*)  displayLink;  //  Method to redraw screen
- (void) didRotate: (NSNotification*) notification; //  Method for movement notifications

@end
