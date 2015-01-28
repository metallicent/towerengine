#version 330

uniform mat4 gl_ModelViewProjectionMatrix;

in vec2 vertex_attr;

out vec2 uv_coord_var;

void main(void)
{
	uv_coord_var = vertex_attr;
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}

