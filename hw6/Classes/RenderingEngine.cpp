//
//  Generic renderer functions
//  No OpenGL here
//

#include "RenderingEngine.h"

//
//  Determine rotation direction
//    0 - match
//    +1 clockwise
//    -i counter-clockwise
float RenderingEngine::RotationDirection() const
{
   float delta = desiredAngle - currentAngle;
   if (delta==0)
     return 0;
   else if ((delta > 0 && delta <= 180) || (delta < -180))
     return +1;
   else
     return -1;
}

//
//  Update current angle during animation
//
void RenderingEngine::UpdateAnimation(float timestep)
{
   //  Direction to rotate during animation
   float direction = RotationDirection();
   //  Animation done
   if (direction == 0) return;
   
   //  Change current angle at 90 deg/sec
   currentAngle +=  direction * 90 * timestep;

   // Normalize the angle to [0, 360)
   while (currentAngle >= 360)
      currentAngle -= 360;
   while (currentAngle < 0)
      currentAngle += 360;
   
   // If the rotation direction changed, then we reached the desired angle.
   if (RotationDirection() != direction) currentAngle = desiredAngle;
}

//
//  Set desired angle when device is rotated
//
void RenderingEngine::OnRotate(DeviceOrientation orientation)
{
   if (orientation == DeviceOrientationLandscapeLeft)
      desiredAngle = 270;
   else if (orientation == DeviceOrientationPortraitUpsideDown)
      desiredAngle = 180;
   else if (orientation == DeviceOrientationLandscapeRight)
      desiredAngle = 90;
   else
      desiredAngle = 0;
}
