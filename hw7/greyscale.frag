// Black and White (absolute)
uniform float dX;
uniform float dY;
uniform float edgenum;
uniform sampler2D img;

vec4 sample(float dx,float dy)
{
   return texture2D(img,gl_TexCoord[0].st+vec2(dx,dy));
}

void main()
{
    
    vec3 edge = vec3(/*edgenum,edgenum,edgenum*/.5,.5,.5);
    vec3 initialcolor = vec3(sample(dX,dY));
    float avgcolor = (initialcolor.r + initialcolor.g + initialcolor.b)/3.0;
    vec3 step1 = step(edge, initialcolor);
    bvec3 boolcolor = bvec3(step1);
    bool whiteorblack = any(boolcolor);
    vec3 wbvec = vec3(float(whiteorblack), float(whiteorblack), float(whiteorblack));
    vec3 color = wbvec*avgcolor;
    
    
    gl_FragColor = vec4(color, 1.0);
}
