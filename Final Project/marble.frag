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


