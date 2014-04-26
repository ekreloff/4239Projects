// Blur (low-pass)
//   1 2 1
//   2 1 2   / 13
//   1 2 1

uniform float dX;
uniform float dY;
uniform sampler2D img;
uniform sampler2D depthtex;
/*
void main(void)
{
    gl_Position = ftransform();
    gl_TexCoord[0] = gl_MultiTexCoord0;
}
*/
float LinearizeDepth(vec2 uv)
{
    float n = 0.01; // camera z near
    float f = 100.0; // camera z far
    float z = texture2D(depthtex, uv).x;
    return (2.0 * n) / (f + n - z * (f - n));
}

vec4 sample(float dx,float dy)
{
   return texture2D(img,gl_TexCoord[0].st+vec2(dx,dy));
}

vec4 sample2(float dx,float dy)
{
    return texture2D(depthtex,gl_TexCoord[0].st+vec2(dx,dy));
}

void main()
{
    
    /*
    float factor = 2.0;
    float samp = sample2(0.0, 0.0).r;
    float denominator = 5.0*d + 4.0*factor*d;
     
    
    float one = d/denominator;
    float two = factor*d/denominator;
    
    
    vec4 depth = vec4(samp, samp, samp, 1.0);
   
   gl_FragColor = one*sample(-dX,+dY) + two*sample(0.0,+dY) + one*sample(+dX,+dY)
                + two*sample(-dX,0.0) + one*sample(0.0,0.0) + two*sample(+dX,0.0)
                + one*sample(-dX,-dY) + two*sample(0.0,-dY) + one*sample(+dX,-dY);*/
    
    vec2 uv = gl_TexCoord[0].xy;
    //vec4 sceneTexel = texture2D(sceneSampler, uv);
    float d;
    d = LinearizeDepth(uv);
    
    
    vec4 final = vec4(d, d, d, 1.0);
    gl_FragColor = final;//mix(nearColor, farColor, smoothstep(near, far, gl_FragCoord.z / gl_FragCoord.w))
    
    float sampleOffset = d/200.0;
    
    vec4 col = vec4(0.0);
    col += texture2D(img, gl_TexCoord[0].st + vec2(-sampleOffset,-sampleOffset)) * 1.0;
    col += texture2D(img, gl_TexCoord[0].st + vec2( 0.0         ,-sampleOffset)) * 2.0;
    col += texture2D(img, gl_TexCoord[0].st + vec2( sampleOffset,-sampleOffset)) * 1.0;
    
    col += texture2D(img, gl_TexCoord[0].st + vec2(-sampleOffset, 0.0     )) * 2.0;
    col += texture2D(img, gl_TexCoord[0].st + vec2( 0.0         , 0.0     )) * 4.0;
    col += texture2D(img, gl_TexCoord[0].st + vec2( sampleOffset, 0.0     )) * 2.0;
    
    col += texture2D(img, gl_TexCoord[0].st + vec2( sampleOffset, sampleOffset)) * 1.0;
    col += texture2D(img, gl_TexCoord[0].st + vec2( 0.0         , sampleOffset)) * 2.0;
    col += texture2D(img, gl_TexCoord[0].st + vec2(-sampleOffset, sampleOffset)) * 1.0;
    
    col /= 16.0;
    
    gl_FragColor = col;
}
