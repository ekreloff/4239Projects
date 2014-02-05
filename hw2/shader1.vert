
void main()
{
    //Position vertexes in space
   gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    //Set color to be based off position, normalized
   gl_FrontColor = (gl_Position/gl_Position[3] + 1.0)*(.5);
}
