//  Derived from Orange Book Chapter 8 by Charles Gruenwald

varying float LightIntensity;


//  granite frag shader

uniform sampler3D Noise3D;
const float Scale = 1.5;


void main(void)
{
    vec4 noisev = texture3D(Noise3D,Scale*gl_TexCoord[0].xyz);
    float intensity = min(1.0, noisev.w * 18.0);
    vec3 color = vec3(intensity * LightIntensity);
    
    
    //  Apply granite color
    gl_FragColor = vec4(color, 1.0);
}

