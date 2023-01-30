#version 330 core

layout(location = 0) out vec4 f_color; //fragmentCOlor

in vec4 v_color;
in vec3 v_position;

void main() {
	float zoom = 0.006;
	vec2 translate = vec2(0.4,0.2);
	f_color = v_color;
	vec2 C = vec2(v_position.x*zoom+translate.x, v_position.y*zoom+translate.y);

	int iteration = 0;
	vec2 Z = vec2(0,0);
	float real = 0;
	float imaginar = 0;

	while(iteration < 1000) {
		float real1 = real;
		float imaginar1 = imaginar;

		float x = Z.x*Z.x - Z.y*Z.y + C.x;
		float y = 2.0*Z.x*Z.y + C.y;

		Z.x = x;
		Z.y = y;
		if(x*x + y*y > 4.0) {
			f_color.r = (iteration*1.0)/1000.0;
			f_color.g = (iteration*1.0)/1000.0;
			f_color.b = (iteration*1.0)/1000.0;
			break;
		}
		iteration ++;
	}
	

	//v_color.r = a_position.y*0.5+0.5;
	//v_color.b = 0.5f;

}

