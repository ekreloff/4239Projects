const char* SimpleFragmentShader = STRINGIFY(
//  Derived from Orange Book Chapter 6 by Charles Gruenwald
                                             
//Stripes
const lowp vec3 StripeSize = vec3(.1,.1,.1);
                                             
// BBall Colors
const lowp vec4 OrangeColor = vec4(1.0, 0.45, 0.0, 0.0);
const lowp vec4 BlackColor = vec4(0.0, 0.0, 0.0, 0.0);
                                             
varying lowp vec3 ModelPos;
varying lowp vec4 Color;

void main(void)
{
    lowp vec3 OrangePct = vec3(.5,.5,.5); //Percent to be orange
                                  //Normalized Position based on texture
    lowp vec3 position = ModelPos/StripeSize;
    //position = position*scale;
    position = fract(position);
    // Determine wether or not to paint orange or black
    lowp vec3 useOrange = step(position,OrangePct);
    // Determine what color to use
    lowp vec4 color  = mix(OrangeColor, BlackColor, useOrange.x*useOrange.y*useOrange.z);
    // Uses positioning and stripes to determine final color
    gl_FragColor = color*Color;
}
);

