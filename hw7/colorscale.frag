// Single color scale
uniform float dX;
uniform float dY;
uniform float colornum;
uniform sampler2D img;

vec4 sample(float dx,float dy)
{
   return texture2D(img,gl_TexCoord[0].st+vec2(dx,dy));
}

void main()
{
    
    float edge = .25;
    float colorselect = float(colornum);
    vec3 initialcolor = vec3(sample(dX,dY));
    float avgcolor = (initialcolor.r + initialcolor.g + initialcolor.b)/3.0;
    float color = step(edge, initialcolor.r)*avgcolor;
    
    if (colorselect == 0.0) {
        gl_FragColor = vec4(color, 0.0, 0.0, 1.0);
    }
    
    if (colorselect == 1.0) {
        gl_FragColor = vec4(0.0, color, 0.0, 1.0);
    }
    
    if (colorselect == 2.0) {
        gl_FragColor = vec4(0.0, 0.0, color, 1.0);
    }
    
    if (colorselect == 3.0) {
        gl_FragColor = vec4(0.0, color, color, 1.0);
    }
    
    if (colorselect == 4.0) {
        gl_FragColor = vec4(color, 0.0, color, 1.0);
    }
    
    if (colorselect == 5.0) {
        gl_FragColor = vec4(color, color, 0.0, 1.0);
    }
}
