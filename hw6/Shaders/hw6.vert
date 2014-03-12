const char* SimpleVertexShader = STRINGIFY(

attribute vec4 XYZW;
attribute vec4 RGBA;
attribute vec3 normal;
                                           
varying vec4 Color;
varying vec3 ModelPos;
                                           
uniform mat4 Projection;
uniform mat4 Modelview;
                                    
                                           

void main(void)
{
    mat3 normalMatrix = mat3(Modelview);
    vec3 eyeNormal = normalize(normalMatrix * normal);
    vec3 lightPosition = vec3(2.0, 2.0, 2.0);
    vec4 diffuseColor = vec4(0.8, 0.8, 0.8, 0.8);
    
    float nDotVP = max(0.0, dot(eyeNormal, normalize(lightPosition)));
    
    Color = diffuseColor * nDotVP * RGBA;
    ModelPos = vec3(XYZW);
    gl_Position = Projection * Modelview * XYZW;
}
                                           
                                           
);
