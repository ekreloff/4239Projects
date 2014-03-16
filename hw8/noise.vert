// Derived from CSCI 4239 examples

varying float LightIntensity;


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







//FAILED ATTEMPT AT BUMPMAPPING (Damn tangent vectors)
/*
// Uniform inputs
//uniform vec3 LightPosition;
//uniform mat4 MVMatrix;
//uniform mat4 MVPMatrix;
//uniform mat3 NormalMatrix;

// Attribute inputs
//attribute vec4 MCVertex;
//attribute vec3 MCNormal;
uniform vec3 MCTangent;
//uniform sampler2D TexCoord0;

//const vec3 upVec = vec3(0.0, 1.0, 0.0);

// Output
varying vec3 LightDir;
varying vec3 EyeDir;
varying vec2 TexCoord;



//  Light intensity and model position required by fragment shader
varying float LightIntensity;
varying vec2  ModelPos;



void main()
{
    vec3 light = vec3(gl_LightSource[0].position);
    //vec3 tangent = normalize(cross(upVec, vec3(gl_Normal)));
    
    
    
    EyeDir = vec3(gl_ModelViewMatrix * gl_Vertex);
    TexCoord = gl_TexCoord[0].st;
 vec3 n = normalize(gl_NormalMatrix * gl_Normal)//gl_Normal;
 vec3 t = normalize(gl_NormalMatrix * MCTangent)//MCTangent;
    vec3 b = cross(n, t);
    vec3 v;
    v.x = dot(light, t);
    v.y = dot(light, b);
    v.z = dot(light, n);
    LightDir = normalize(v);
    v.x = dot(EyeDir, t);
    v.y = dot(EyeDir, b);
    v.z = dot(EyeDir, n);
    EyeDir = normalize(v);
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    
    
    
   //  Scalar light intensity (for fragment shader)
   LightIntensity = phong();
   //  Save model coordinates (for fragment shader)
   ModelPos = gl_Vertex.xy;
   //  Return fixed transform coordinates for this vertex
   gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
   // Set color by position
   gl_FrontColor = 0.5*(gl_Position/gl_Position[3] + 1.0);
    
}



//  Phong lighting intensity only
float phong()
    {
        //  P is the vertex coordinate on body
        vec3 P = vec3(gl_ModelViewMatrix * gl_Vertex);
        //  N is the object normal at P
        vec3 N = normalize(gl_NormalMatrix * gl_Normal);
        //  Light Position for light 0
        vec3 LightPos = vec3(gl_LightSource[0].position);
        //  L is the light vector
        vec3 L = normalize(LightPos - P);
        //  R is the reflected light vector R = 2(L.N)N - L
        vec3 R = reflect(-L, N);
        //  V is the view vector (eye at the origin)
        vec3 V = normalize(-P);
        
        //  Diffuse light intensity is cosine of light and normal vectors
        float Id = max(dot(L,N) , 0.0);
        //  Shininess intensity is cosine of light and reflection vectors to a power
        float Is = (Id>0.0) ? pow(max(dot(R,V) , 0.0) , gl_FrontMaterial.shininess) : 0.0;
        
        //  Vertex color (ignores emission and global ambient)
        vec3 color = gl_FrontLightProduct[0].ambient.rgb
        + Id*gl_FrontLightProduct[0].diffuse.rgb
        + Is*gl_FrontLightProduct[0].specular.rgb;
        
        //  Vertex intensity
        return length(color);
    }*/