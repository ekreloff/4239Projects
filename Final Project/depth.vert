varying vec4 vertColor;

void main() {
    gl_Position =  gl_ModelViewMatrix * gl_Vertex;
    gl_Color = gl_Color;
}