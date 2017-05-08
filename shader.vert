#version 130

varying vec3 g_normal;
varying vec4 g_object_position;

uniform mat4 g_projection_matrix;
uniform mat4 g_modelview_matrix;
uniform mat3 g_normal_matrix;

void main(void)
{
	g_object_position = g_modelview_matrix * vec4(gl_Vertex.xyz, 1.0);
	g_normal = normalize(g_normal_matrix * gl_Normal);
	gl_Position = g_projection_matrix * g_object_position;
}

