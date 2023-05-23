#version 450 // version of GLSL to use

//
vec2 positions[3] = vec2[](
    vec2(0.0, -0.5),
    vec2(0.5, 0.5),
    vec2(-0.5, 0.5)
);

// input from vertex shader and outputs to fragment shader
// This function is run once for each vertex
void main() {
    // gl_Position is a special variable that holds the position of a vertex (meaning this is our output for this vertex)
    gl_Position = vec4(positions[gl_VertexIndex], 0.0, 1.0);
    // vec4(x=[-1,1], y=[-1,1], z=depth, w=1.0) is the position of the vertex
    // gl_VertexIndex is the index of the vertex (0, 1, 2)
}
