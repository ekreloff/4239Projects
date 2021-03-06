
/* *******************************************************
 * Created By Ethan Kreloff April 8th, 2014.
 *********************************************************
 * Based off of code from the Orange Book Chapter 8 by
 * Charles Gruenwald and sample code from CSCI 4239/5239
 * at University of Colorado at Boulder.
 * *******************************************************
 * Shader creates noise for a vertex shader.
 * *******************************************************
 * noise.vert
 * ******************************************************/

varying float LightIntensity;
varying vec2 texCoord;

vec4 phong()
{
    //  P is the vertex coordinate on body
    vec3 P = vec3(gl_ModelViewMatrix * gl_Vertex);
    //  N is the object normal at P
    vec3 N = normalize(gl_NormalMatrix * gl_Normal);
    //  Light Position for light 0
    vec3 LightPos = vec3(gl_LightSource[0].position);
    //  L is the light vector
    vec3 L = normalize(LightPos - P);
    
    LightIntensity = dot(L, N);
    LightIntensity *= 1.5;
    
    
    //  Emission and ambient color
    vec4 color = gl_FrontMaterial.emission + gl_FrontLightProduct[0].ambient + gl_LightModel.ambient*gl_FrontMaterial.ambient;
    
    //  Diffuse light intensity is cosine of light and normal vectors
    float Id = dot(L,N);
    if (Id>0.0)
    {
        //  Add diffuse
        color += Id*gl_FrontLightProduct[0].diffuse;
        //  R is the reflected light vector R = 2(L.N)N - L
        vec3 R = reflect(-L, N);
        //  V is the view vector (eye at the origin)
        vec3 V = normalize(-P);
        //  Specular is cosine of reflected and view vectors
        float Is = dot(R,V);
        if (Is>0.0) color += pow(Is,gl_FrontMaterial.shininess)*gl_FrontLightProduct[0].specular;
    }
    
    //  Return sum of color components
    return color;
}


void main()
{
    //  Vertex color
    gl_FrontColor = phong();
    
    //  Texture coordinate
    gl_TexCoord[0] = gl_Vertex;
    
    
    //  Return fixed transform coordinates for this vertex
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}




