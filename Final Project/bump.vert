
/* *******************************************************
 * Created By Ethan Kreloff April 8th, 2014.
 *********************************************************
 * Based off of code from
 * http://www.thetenthplanet.de/archives/1180
 * http://www.geeks3d.com/20130122/normal-mapping-without-precomputed-tangent-space-vectors/
 * *******************************************************
 * Shader that adds texture to an object based
 * off of a bump map.
 * *******************************************************
 * bump.vert
 * ******************************************************/


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
    
    
}

