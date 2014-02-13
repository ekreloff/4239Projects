//  Derived from Orange Book Chapter 6 by Charles Gruenwald

//Stripes
const vec2 StripeSize = vec2(.1,.1);


// BBall Colors
const vec3 OrangeColor = vec3(1.0, 0.45, 0.0);
const vec3 OrangeColor2 = vec3(1.0, 0.65, 0.0);
const vec3 OrangeColor3 = vec3(1.0, 0.8, 0.0);
const vec3 BlackColor = vec3(0.0, 0.0, 0.0);
//  Model coordinates and light from vertex shader
varying float LightIntensity;
varying vec2  ModelPos;
uniform float time;

void main()
{
   vec2 OrangePct = vec2(.9,.9); //Percent to be orange
   //Normalized Position based on texture
   vec2 position = ModelPos/StripeSize;
   position = fract(position);
   // Determine wether or not to paint orange or black
   vec2 useOrange = step(position, OrangePct);
   // Determine what color to use
   vec3 color = vec3(0.0,0.0,0.0);
   switch(mod(time, 3.0)){
	   case 0.0:
		color = mix(OrangeColor, BlackColor, useOrange.x*useOrange.y);
		break;
	   case 1.0:
		color = mix(OrangeColor, BlackColor, useOrange.x*useOrange.y);
		break;
	   case 2.0:
	    color = mix(OrangeColor, BlackColor, useOrange.x*useOrange.y);
	    break;
	}
   //  Adjust color intensity for lighting (interpolated from vertex shader values)
   color *= LightIntensity;
   // Uses positioning and stripes to determine final color
   gl_FragColor = vec4(color,1.0)*gl_Color; 
   
}
