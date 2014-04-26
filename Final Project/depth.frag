vec4 nearColor = vec4(1.0, 1.0, 1.0, 1.0);
vec4 farColor = vec4(0.0, 0.0, 0.0, 1.0);
float near = 0.0;
float far = 1.0;

varying vec4 vertColor;

void main() {
    gl_FragColor = mix(nearColor, farColor, smoothstep(near, far, gl_FragCoord.z / gl_FragCoord.w));
}