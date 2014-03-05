// Blur (low-pass)
//   1 2 1
//   2 1 2   / 13
//   1 2 1

uniform float dX;
uniform float dY;
uniform sampler2D img;

vec4 sample(float dx,float dy)
{
    return texture2D(img,gl_TexCoord[0].st+vec2(dx,dy));
}

void main()
{
    gl_FragColor = vec4(1.0 - sample(dX,dY).rgb, 1.0);
}
