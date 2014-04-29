/* *******************************************************
 * Created By Ethan Kreloff April 8th, 2014.
 * *******************************************************
 * Shader that adds a premade mask image to effect the
 * drawing of the scene.
 * *******************************************************
 * mask.frag
 * ******************************************************/

uniform sampler2D mask;
uniform float alphaDist;

void main()
{

    
    vec2 texPosition = (gl_TexCoord[0].xy + vec2(1.5, 0.7)) * vec2(1.0,.25);
    vec4 maskVec = texture2D(mask, texPosition);
    float alpha = (maskVec.r + maskVec.g + maskVec.b)/3.0;
    vec4 color = maskVec * vec4(0.1,0.1,0.1,(1.0 - alpha));
    color.a *= 4.0/(alphaDist + 4.0) - 0.5;
   
    gl_FragColor = color;

}
