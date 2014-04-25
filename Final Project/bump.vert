



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

/*
// Derived from CSCI 4239 examples
varying vec3 Vertex_LightDir;
varying vec3 Vertex_EyeVec;
varying vec3 Vertex_Normal;

const uniform vec4 uv_tiling = (2.0, 2.0, 1.0, 1.0);

void main()
{
    vec3 LightPos = vec3(gl_LightSource[0].position);
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    gl_TexCoord[0] = gl_MultiTexCoord0 * uv_tiling;
    Vertex_Normal = gl_NormalMatrix * gl_Normal;
    vec4 view_vertex = gl_ModelViewMatrix * gl_Vertex;
    Vertex_LightDir = LightPosition.xyz - view_vertex.xyz;
}



varying vec3 lightVec;
varying vec3 eyeVec;
varying vec2 texCoord;
attribute vec3 vTangent;

varying vec3 g_vertexnormal;
varying	vec3 g_viewvector;  // camera pos - vertex pos
varying vec2 g_texcoord;


void main(void)
{
    
    
   
	
    g_vertexnormal = gl_NormalMatrix * gl_Normal;
    g_viewvector = vec3(gl_ModelViewMatrix * gl_Vertex);
	g_texcoord = gl_MultiTexCoord0.xy;
    
    //  Vertex color
    // gl_FrontColor = phong();
    
    //  Texture coordinate
    //gl_TexCoord[0] = gl_Vertex;
    
    //  Texture coordinate for fragment shader
    //texCoord = gl_MultiTexCoord0.xy;
    
    //  Return fixed transform coordinates for this vertex
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}







/*
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
    
    //  Texture coordinate for fragment shader
    //texCoord = gl_MultiTexCoord0.xy;
    
    //  Return fixed transform coordinates for this vertex
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}


//uniform float time;
//uniform float frequency;

varying vec3 vNormal;
varying vec4 vVertex;
//varying vec4 vVertex;

vec3 computeNormal( vec3 pos,
                   vec3 tangent,
                   vec3 binormal)
{
	mat3 J;
	
	float dist = sqrt(pos.x*pos.x + pos.z*pos.z);
	//float jac_coef = cos(freq*dist + phase) / (dist+0.00001);
	
	// A matrix is an array of column vectors so J[2] is
	// the third column of J.
	
	J[0][0] = 1.0;
 J[0][1] = /*jac_coef * ///pos.x;
	J[0][2] = 0.0;
	
	J[1][0] = 0.0;
	J[1][1] = 1.0;
	J[1][2] = 0.0;
    
	J[2][0] = 0.0;
J[2][1] = /*jac_coef * ///pos.z;
	J[2][2] = 1.0;
	
	vec3 u = J * tangent;
	vec3 v = J * binormal;
	
	vec3 n = cross(v, u);
	return normalize(n);
}
*/

/*vec4 displaceVertexFunc( vec4 pos, float phase, float frequency )
{
	vec4 new_pos;
	
	new_pos.x = pos.x;
	new_pos.z = pos.z;
	new_pos.w = pos.w;
	
	float dist = sqrt(pos.x*pos.x + pos.z*pos.z);
	new_pos.y = pos.y + 20.0 * sin( frequency * dist + phase );
	
	return new_pos;
}

void main(void)
{
	//vec4 displacedVertex;
	vec3 displacedNormal;
	
	// 1 - Compute the diplaced position.
	//
	//displacedPosition = displaceVertexFunc(gl_Vertex, time*2.0, frequency );
   	
 gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex/*displacedPosition///;
	//vVertex = gl_ModelViewMatrix * displacedPosition;
	
	
	// 2 - Compute the displaced normal
	//
	
	// if the engine does not provide the tangent vector you
	// can compute it with the following piece of of code:
	//
	vec3 tangent;
	vec3 binormal;
	
	vec3 c1 = cross(gl_Normal, vec3(0.0, 0.0, 1.0));
	vec3 c2 = cross(gl_Normal, vec3(0.0, 1.0, 0.0));
	
	if(length(c1)>length(c2))
	{
		tangent = c1;
	}
	else
	{
		tangent = c2;
	}
	
	tangent = normalize(tangent);
	
	binormal = cross(gl_Normal, tangent);
	binormal = normalize(binormal);
    
	displacedNormal = computeNormal( gl_Vertex.xyz,
                                    tangent.xyz,
                                    binormal);
   	
   	vNormal = normalize(gl_NormalMatrix * displacedNormal);
    vVertex = gl_Vertex;
}

/*

////////////////////////////////////////////////////////////////
// Vertex shader for procedural bumps
// Authors: Randi Rost, John Kessenich
// Copyright (c) 2002-2005 3Dlabs Inc. Ltd.
// See 3Dlabs-License.txt for license information

varying vec3 LightDir;
varying vec3 EyeDir;

uniform vec3 LightPosition;

//attribute vec3 Tangent;

void main(void)
{
    
    vec3 tangent;
    vec3 binormal;
    
    vec3 c1 = cross(gl_Normal, vec3(0.0, 0.0, 1.0));
    vec3 c2 = cross(gl_Normal, vec3(0.0, 1.0, 0.0));
    
    if(length(c1)>length(c2))
    {
        tangent = c1;
    }
    else
    {
        tangent = c2;
    }
    
    tangent = normalize(tangent);
    
    binormal = cross(gl_Normal, tangent);
    binormal = normalize(binormal);
    
    
	EyeDir = vec3 (gl_ModelViewMatrix * gl_Vertex);
    
	gl_Position = ftransform();
	gl_TexCoord[0] = gl_MultiTexCoord0;
    
	// convert normal and tangent (from main program) into eye space
	vec3 n = normalize(gl_NormalMatrix * gl_Normal);
	vec3 t = normalize(gl_NormalMatrix * Tangent);
    
	// compute b in eye space
	vec3 b = cross(n, t);
    
	// convert light direction from eye space to tangent space
	vec3 v;
	v.x = dot(LightPosition, t);
	v.y = dot(LightPosition, b);
	v.z = dot(LightPosition, n);
	LightDir = normalize(v);
    
	// convert eye direction from eye space to tangent space
	v.x = dot(EyeDir, t);
	v.y = dot(EyeDir, b);
	v.z = dot(EyeDir, n);
	EyeDir = normalize(v);
}

*/