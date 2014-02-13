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

vec2 func1();
vec2 func2(vec2 v);
vec2 func3(vec2 v, vec2 v2);
vec3 func4(vec3 v);

void main()
{
   vec2 OrangePct = vec2(.9,.9); //Percent to be orange
   //Normalized Position based on texture
   vec2 position = func1();
   position = func2(position);
   // Determine wether or not to paint orange or black
   vec2 useOrange = func3(position, OrangePct);
   // Determine what color to use
   vec3 color = mix(OrangeColor, BlackColor, useOrange.x*useOrange.y);
   //  Adjust color intensity for lighting (interpolated from vertex shader values)
   color = func4(color);
   // Uses positioning and stripes to determine final color
   gl_FragColor = vec4(color,1.0)*gl_Color; 
   
}

vec2 func1()
{
	return ModelPos/StripeSize;
}

vec2 func2(vec2 v)
{
	return fract(v);
}

vec2 func3(vec2 v, vec2 v2)
{
		return step(v,v2);
}

vec3 func4(vec3 v)
{
	return v *= LightIntensity;
}


