// Derived from CSCI 4239 examples

varying float LightIntensity;
varying vec2 texCoord;


/*
varying vec3 Vertex_LightDir;
varying vec3 Vertex_EyeVec;
varying vec3 Vertex_Normal;

varying vec4 light_diffuse;
varying vec4 material_diffuse;
varying vec4 light_specular;
varying vec4 material_specular;
varying float material_shininess;

void main()
{
    vec3 LightPos = vec3(gl_LightSource[0].position);
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    gl_TexCoord[0] = gl_MultiTexCoord0;
    Vertex_Normal = gl_NormalMatrix * gl_Normal;
    vec4 view_vertex = gl_ModelViewMatrix * gl_Vertex;
    Vertex_LightDir = LightPos.xyz - view_vertex.xyz;
    Vertex_EyeVec = -view_vertex.xyz;
    
    light_diffuse = gl_FrontLightProduct[0].diffuse;
    material_diffuse = gl_FrontMaterial.diffuse;
    light_specular = gl_FrontLightProduct[0].specular;
    material_specular = gl_FrontMaterial.specular;
    material_shininess = gl_FrontMaterial.shininess;
    
    
}*/

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
    
    //  Texture coordinate for fragment shader
    //texCoord = gl_MultiTexCoord0.xy;
    
    //  Return fixed transform coordinates for this vertex
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}




