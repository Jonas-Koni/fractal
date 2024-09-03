#version 330 core

layout(location = 0) in vec3 a_position; //attribut
layout(location = 1) in vec4 a_color;
layout(location = 2) in vec3 a_scale;

out vec4 v_color;
out vec3 v_position;
out vec3 v_scale;

void main() {
	gl_Position = vec4(a_position, 1.0f);
	v_position = a_position;
	v_scale = a_scale;
	

}