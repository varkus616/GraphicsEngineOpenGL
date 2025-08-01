#version 330 core
layout (triangles) in;
layout (line_strip, max_vertices = 6) out;

in VS_OUT {
    vec3 normal;
    vec4 color;
} gs_in[];

const float MAGNITUDE = 0.2;
  
uniform mat4 proj_matrix;
out vec4 color;

void GenerateLine(int index)
{
    gl_Position = proj_matrix * gl_in[index].gl_Position;
    EmitVertex();
    gl_Position = proj_matrix * (gl_in[index].gl_Position + 
                                vec4(gs_in[index].normal, 0.0) * MAGNITUDE);
    color = gs_in[index].color;  // Set the color for this vertex
    EmitVertex();
    EndPrimitive();
}

void main()
{
    GenerateLine(0); // first vertex normal
    GenerateLine(1); // second vertex normal
    GenerateLine(2); // third vertex normal
}  