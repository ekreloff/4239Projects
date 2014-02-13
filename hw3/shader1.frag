//  Derived from Orange Book Chapter 6 by Charles Gruenwald

//Stripes
const vec2 StripeSize = vec2(.1,.1);


// BBall Colors
const vec3 OrangeColor = vec3(1.0, 0.45, 0.0);
const vec3 BlackColor = vec3(0.0, 0.0, 0.0);
//  Model coordinates and light from vertex shader
varying float LightIntensity;
varying vec2  ModelPos;
uniform float time;

void main()
{
   //float current = (cos(time*10.0)+1.0)/2.0;
   //vec3 currentVec = vec3(current*.9, current*.8, current*.7);
   vec2 OrangePct = vec2(.9,.9); //Percent to be orange
   //Normalized Position based on texture
   vec2 position = ModelPos/StripeSize;
   //position = position*scale;
   position = fract(position);
   // Determine wether or not to paint orange or black
   vec2 useOrange = step(position,OrangePct);
   // Determine what color to use
   vec3 color  = mix(OrangeColor, BlackColor, useOrange.x*useOrange.y);
   //  Adjust color intensity for lighting (interpolated from vertex shader values)
   color *= LightIntensity;
   // adjust color over time
   //color += currentVec;
   // Uses positioning and stripes to determine final color
   gl_FragColor = vec4(color,1.0)*gl_Color; 
   
}
