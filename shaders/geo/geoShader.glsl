#version 430 core

layout (points) in;
layout (points, max_vertices=3) out;

uniform mat4 model_view_matrix;
uniform mat4 projection_matrix;
uniform vec4 FrustumPlanes[6];

bool PointInFrustum(in vec3 p)
{
	for(int i = 0; i < 6; i++)
	{
		vec4 plane=FrustumPlanes[i];
		if (( dot(plane.xyz, p) + plane.w) < 0)
			return false;
	}
	return true;
}

void main() 
{
	for (int i = 0; i < gl_in.length; i++)
	{
		vec4 vInPos = gl_in[i].gl_Position;
		vec2 tmp = (vInPos.xz*2-1.0) * 5;
		vec3 V = vec3(tmp.x, vInPos.y, tmp.y);
		gl_Position = model_view_matrix * projection_matrix * vec4(V, 1);

		if (PointInFrustum(V)){
			EmitVertex();
		}
	}
	EndPrimitive();

}