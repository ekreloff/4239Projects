// Derived from CSCI 4239 examples
/*
varying vec3 lightVec;
varying vec3 eyeVec;
varying vec2 texCoord;
uniform sampler2D colorMap;
uniform sampler2D normalMap;
uniform float invRadius;*/



uniform sampler2D tex0;
uniform sampler2D tex1;

varying vec4 light_diffuse;
varying vec4 material_diffuse;
varying vec4 light_specular;
varying vec4 material_specular;
varying float material_shininess;

varying vec3 Vertex_LightDir;
varying vec3 Vertex_EyeVec;
varying vec3 Vertex_Normal;

// http://www.thetenthplanet.de/archives/1180
mat3 cotangent_frame(vec3 N, vec3 p, vec2 uv)
{
    // get edge vectors of the pixel triangle
    vec3 dp1 = dFdx( p );
    vec3 dp2 = dFdy( p );
    vec2 duv1 = dFdx( uv );
    vec2 duv2 = dFdy( uv );
    
    // solve the linear system
    vec3 dp2perp = cross( dp2, N );
    vec3 dp1perp = cross( N, dp1 );
    vec3 T = dp2perp * duv1.x + dp1perp * duv2.x;
    vec3 B = dp2perp * duv1.y + dp1perp * duv2.y;
    
    // construct a scale-invariant frame
    float invmax = inversesqrt( max( dot(T,T), dot(B,B) ) );
    return mat3( T * invmax, B * invmax, N );
}

vec3 perturb_normal( vec3 N, vec3 V, vec2 texcoord )
{
    // assume N, the interpolated vertex normal and
    // V, the view vector (vertex to eye)
    vec3 map = texture2D(tex1, texcoord ).xyz;
    map = map * 255./127. - 128./127.;
    mat3 TBN = cotangent_frame(N, -V, texcoord);
    return normalize(TBN * map);
}



void main()
{
    vec2 uv = gl_TexCoord[0].xy;
    
    vec3 N = normalize(Vertex_Normal.xyz);
    vec3 L = normalize(Vertex_LightDir.xyz);
    vec3 V = normalize(Vertex_EyeVec.xyz);
    vec3 PN = perturb_normal(N, V, uv);
    
    vec4 tex01_color = texture2D(tex0, uv).rgba;
    vec4 final_color = vec4(0.2, 0.15, 0.15, 1.0) * tex01_color;
    
    float lambertTerm = dot(PN, L);
    if (lambertTerm > 0.0)
    {
        final_color += light_diffuse * material_diffuse * lambertTerm * tex01_color;
        
        
        vec3 E = normalize(Vertex_EyeVec.xyz);
        vec3 R = reflect(-L, PN);
        float specular = pow( max(dot(R, E), 0.0), material_shininess);
        final_color += light_specular * material_specular * specular;
    }
    gl_FragColor.rgb = final_color.rgb;
    //gl_FragColor.rgb = normal.rgb;
    //gl_FragColor.rgb = N.rgb;
    gl_FragColor.a = 1.0;
}


/*
varying vec3 g_vertexnormal;
varying	vec3 g_viewvector;  // camera pos - vertex pos
varying vec2 g_texcoord;

mat3 cotangent_frame( vec3 N, vec3 p, vec2 uv )
{
    // get edge vectors of the pixel triangle
    vec3 dp1 = dFdx( p );
    vec3 dp2 = dFdy( p );
    vec2 duv1 = dFdx( uv );
    vec2 duv2 = dFdy( uv );
    
    // solve the linear system
    vec3 dp2perp = cross( dp2, N );
    vec3 dp1perp = cross( N, dp1 );
    vec3 T = dp2perp * duv1.x + dp1perp * duv2.x;
    vec3 B = dp2perp * duv1.y + dp1perp * duv2.y;
    
    // construct a scale-invariant frame
    float invmax = inversesqrt( max( dot(T,T), dot(B,B) ) );
    return mat3( T * invmax, B * invmax, N );
}

vec3 perturb_normal( vec3 N, vec3 V, vec2 texcoord )
{
    // assume N, the interpolated vertex normal and
    // V, the view vector (vertex to eye)
    vec3 map = texture2D( mapBump, texcoord ).xyz;
    /*
#ifdef WITH_NORMALMAP_UNSIGNED
    map = map * 255./127. - 128./127.;
#endif
#ifdef WITH_NORMALMAP_2CHANNEL
    map.z = sqrt( 1. - dot( map.xy, map.xy ) );
#endif
#ifdef WITH_NORMALMAP_GREEN_UP
    map.y = -map.y;
#endif
 
    mat3 TBN = cotangent_frame( N, -V, texcoord );
    return normalize( TBN * map );
}

vec4 phong()
{
    vec3 N = normalize( g_vertexnormal );
     N = perturb_normal( N, g_viewvector, g_texcoord );
    
    
    //  P is the vertex coordinate on body
    vec3 P = vec3(gl_ModelViewMatrix * gl_Vertex);
    //  N is the object normal at P
    vec3 N = normalize(gl_NormalMatrix * gl_Normal);
    //  Light Position for light 0
    vec3 LightPos = vec3(gl_LightSource[0].position);
    //  L is the light vector
    vec3 L = normalize(LightPos - P);
    
    float LightIntensity = dot(L, N);
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
    return color * LightIntensity;
}



void main (void)
{
	
	gl_FragColor = phong();
}




/*
//varying vec2 texCoord;
varying vec3 vNormal;
varying vec4 vVertex;

vec4 phong()
{
    //  P is the vertex coordinate on body
    vec3 P = vec3(gl_ModelViewMatrix * vVertex);
    //  N is the object normal at P
    vec3 N = normalize(gl_NormalMatrix * vNormal);
    //  Light Position for light 0
    vec3 LightPos = vec3(gl_LightSource[0].position);
    //  L is the light vector
    vec3 L = normalize(LightPos - P);
    
    float LightIntensity = dot(L, N);
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
    return color * LightIntensity;
}

void main()
{
    //  Vertex color
    gl_FragColor = phong();
    
    //  Texture coordinate
    //gl_TexCoord[0] = gl_Vertex;
    
    //  Texture coordinate for fragment shader
    //texCoord = gl_MultiTexCoord0.xy;
    
    //  Return fixed transform coordinates for this vertex
    //gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}


//
// Fragment shader for procedural bumps
//
// Authors: Randi Rost, John Kessenich
//
// Copyright (c) 2002-2005 3Dlabs Inc. Ltd.
//
// See 3Dlabs-License.txt for license information
//

varying vec3 LightDir;
varying vec3 EyeDir;

uniform vec3  SurfaceColor;    // = (0.7, 0.6, 0.18)
uniform float BumpDensity;     // = 16.0
uniform float BumpSize;        // = 0.15
uniform float SpecularFactor;  // = 0.5

void main (void)
{
    vec3 litColor;
    vec2 c = BumpDensity * gl_TexCoord[0].st;
    vec2 p = fract(c) - vec2(0.5);
    
    float d, f;
    d = p.x * p.x + p.y * p.y;
    f = 1.0 / sqrt(d + 1.0);
    
    if (d >= BumpSize)
    { p = vec2(0.0); f = 1.0; }
    
    vec3 normDelta = vec3(p.x, p.y, 1.0) * f;
    litColor = SurfaceColor * max(dot(normDelta, LightDir), 0.0);
    vec3 reflectDir = reflect(LightDir, normDelta);
    
    float spec = max(dot(EyeDir, reflectDir), 0.0);
    spec *= SpecularFactor;
    litColor = min(litColor + spec, vec3(1.0));
    
    gl_FragColor = vec4(litColor, 1.0);
}*/

