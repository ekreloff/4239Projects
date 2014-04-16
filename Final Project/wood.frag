//  Derived from Orange Book Chapter 8 by Charles Gruenwald

varying float LightIntensity;
varying vec2 texCoord;

//  wood frag shader

uniform sampler3D Noise3D;
uniform sampler2D CourtTex0;

uniform float RingFreq;
uniform float LightGrains;
uniform float DarkGrains;
uniform float GrainThreshold;
uniform float Noisiness;
uniform float GrainScale;
uniform float Scale;

uniform vec3 LightWood;
uniform vec3 DarkWood;
uniform vec3 NoiseScale;




void main(void)
{
    vec4 logo = texture2D(CourtTex0,texCoord);
    vec3 MCposition = Scale*gl_TexCoord[0].xyz;
    vec3 noisev = vec3(texture3D(Noise3D,MCposition * NoiseScale) * Noisiness);
    vec3 location = MCposition + noisev;
    float dist = sqrt(/*location.x*location.x + */location.z*location.z);
    dist *= RingFreq;
    float r = fract(dist + noisev[0] + noisev[1] + noisev[2])*2.0;
    if(r > 1.0){
        r = 2.0 - r;
    }
    vec3 color =  mix(LightWood, DarkWood, r);
    r = fract((/*MCposition.x +*/ MCposition.z)*GrainScale + 0.5);
    noisev[2] *= r;
    if (r < GrainThreshold) {
        color += LightWood * LightGrains * noisev[2];
    }else{
        color -= LightWood * LightGrains * noisev[2];
    }
    color *= LightIntensity;
    //  Apply final color
    gl_FragColor = vec4(color, 1.0);
}

