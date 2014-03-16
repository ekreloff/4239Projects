//  Derived from Orange Book Chapter 8 by Charles Gruenwald

varying float LightIntensity;


//  granite frag shader

uniform sampler3D Noise3D;

const vec4 Vein   = vec4(0.0,0.0,0.5,1.0);
const vec4 Marble = vec4(0.8,0.8,0.8,1.0);
const float Scale = 1.5;


void main(void)
{
    vec3 MCposition = Scale*gl_TexCoord[0].xyz;
    vec4 noisev = texture3D(Noise3D,MCposition);
    float intensity = abs(noisev[0] - 0.25)
    + abs(noisev[1] - 0.125)
    + abs(noisev[2] - 0.0625)
    + abs(noisev[3] - 0.03125);
    float sineval = sin(MCposition.y * 6.0 + intensity * 12.0) * .5 + .5;
    vec4 color = mix(Vein, Marble, sineval) * LightIntensity;
    
    
    //  Apply granite color
    gl_FragColor = color;
}









//FAILED ATTEMPT AT BUMPMAPPING (Damn tangent vectors)
/*
const vec4 SurfaceColor = vec4(.7, .6, .18, 1.0);
const float BumpDensity = 16.0;
const float BumpSize = .15;
const float SpecularFactor = .5;

varying vec3 LightDir;
varying vec3 EyeDir;
varying vec2 TexCoord;


void main(){
    vec3 litColor;
    vec2 c = BumpDensity * TexCoord.st;
    vec2 p = fract(c) - vec2(0.5);
    
    float d, f;
    d = dot(p, p);
    f = 1.0/sqrt(d + 1.0);
    
    if (d >= BumpSize) {
        p = vec2(0.0, 0.0);
        f = 1.0;
    }
    
    vec3 normDelta = vec3(p.x, p.y, 1.0) * f;
    litColor = SurfaceColor.rgb * max(dot(normDelta, LightDir), 0.0);
    vec3 reflectDir = LightDir - 2.0 * dot(normDelta, LightDir) * normDelta;
    
    float spec = max(dot(EyeDir, reflectDir), 0.0);
    spec = pow(spec, 6.0);
    spec *= SpecularFactor;
    litColor = min(litColor + spec, vec3(1.0));
    
    gl_FragColor = vec4(litColor, SurfaceColor.a);
}



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
 */
