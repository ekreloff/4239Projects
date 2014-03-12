// Black and White (absolute)
uniform float dX;
uniform float dY;
uniform sampler2D img;

vec4 sample(float dx,float dy)
{
   return texture2D(img,gl_TexCoord[0].st+vec2(dx,dy));
}

void main()
{
    
    vec3 edge = vec3(0.5,0.5,0.5);
    vec3 step1 = step(edge, vec3(sample(dX,dY)));
    bvec3 boolcolor = bvec3(step1);
    bool whiteorblack = any(boolcolor);
    vec3 color = vec3(float(whiteorblack), float(whiteorblack), float(whiteorblack));
    
    gl_FragColor = vec4(color, 1.0);
}