//  Derived from Orange Book Chapter 6 by Charles Gruenwald

//Stripes
uniform sampler2D mask;
uniform float alphaDist;

void main()
{
   //Percent to be ora
   // Uses positioning and stripes to determine final color
    
    vec2 texPosition = (gl_TexCoord[0].xy + vec2(1.5, 0.7)) * vec2(1.0,.25);
    vec4 maskVec = texture2D(mask, texPosition);
    float alpha = (maskVec.r + maskVec.g + maskVec.b)/3.0;
    vec4 color = maskVec * vec4(0.1,0.1,0.1,(1.0 - alpha));
    color.a *= 4.0/(alphaDist + 4.0) - 0.5;
   
    gl_FragColor = color;

}
