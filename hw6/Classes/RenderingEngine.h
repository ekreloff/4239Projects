//
//  OpenGL Renderer
//
//  Base class for both OpenGL ES 1.1 and OpenGL ES 2.0
//
#ifndef RENDERINGENGINE_H
#define RENDERINGENGINE_H

// Physical orientation of a handheld device, equivalent to UIDeviceOrientation
enum DeviceOrientation
{
   DeviceOrientationUnknown,
   DeviceOrientationPortrait,
   DeviceOrientationPortraitUpsideDown,
   DeviceOrientationLandscapeLeft,
   DeviceOrientationLandscapeRight,
   DeviceOrientationFaceUp,
   DeviceOrientationFaceDown,
};

//
//  Base OpenGL ES renderer class
//  Virtual method must be reimplemented for ES 1.1 and ES 2.0
//
class RenderingEngine
{
public:
   virtual void Initialize(int width,int height) = 0;    //  Initialize to this size
   virtual void Display(float t) = 0;                    //  Display the scene
   virtual ~RenderingEngine() {}                         //  Destructor
   void UpdateAnimation(float timestep);                 //  Set current angle in animation
   void OnRotate(DeviceOrientation newOrientation);      //  Set destination angle for animation
private:
   float RotationDirection() const;                      //  Helper to decide rotation direction
protected:
   float desiredAngle;                                   //  Desired up angle
   float currentAngle;                                   //  Current up angle (changed in animation)
   unsigned int renderbuffer;                            //  Render buffer name
};

// Create an instance of the renderer and set up various OpenGL state.
RenderingEngine* CreateRenderer1();  // OpenGL ES 1.1
RenderingEngine* CreateRenderer2();  // OpenGL ES 2.0

#endif
