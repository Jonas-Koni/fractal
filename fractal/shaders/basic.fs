#version 330 core

#define E 2.71828184590
layout(location = 0) out vec4 f_color; //fragmentCOlor

in vec4 v_color;
in vec3 v_position;

uniform vec4 v_scale;
float scale = pow(v_scale.z, v_scale.a); 
int MaxIteration = 600;

vec2 const_i = vec2(0,1);
vec2 const_1 = vec2(1,0);
vec2 const_2 = vec2(2,0);
vec2 const_3 = vec2(3,0);

//to Polar: 
//radius = dist to 0;0
//angle = atan(imaginar/real)

//to Cartesic
//real: radius*cos(angle);
//imaginar: radius*sin(angle);

float mod(float a, float b) {
	return a-(b*floor(a/b));
}

vec3 hsvToRgb(vec3 HSV) {
	HSV.x = mod(HSV.x, 360.0);///60.0;
	HSV.y = mod(HSV.y, 100.0);///100.0;
	HSV.z = mod(HSV.z, 100.0);///100.0;

	float C = HSV.z*HSV.y;
	float X = C*(1-abs(mod(HSV.x,2)-1.0));
	float m = HSV.z-C;

	vec3 RGB;

	if(HSV.x < 1){
		RGB.x = C;
		RGB.y = X;
		RGB.z = 0; //vec3(C, X, 0);
	} else if (HSV.x < 2){
		RGB.x = X;
		RGB.y = C;
		RGB.z = 0;
	} else if (HSV.x < 3){
		RGB.x = 0;
		RGB.y = C;
		RGB.z = X;
	} else if (HSV.x < 4){
		RGB.x = 0;
		RGB.y = X;
		RGB.z = C;
	} else if (HSV.x < 5){
		RGB.x = X;
		RGB.y = 0;
		RGB.z = C;
	} else if (HSV.x < 6){
		RGB.x = C;
		RGB.y = 0;
		RGB.z = X;
	} else {
		RGB.x = C;
		RGB.y = 0;
		RGB.z = X;
	}
	RGB.x += m;
	RGB.y += m;
	RGB.z += m;

	return vec3(RGB);
}

vec2 add(vec2 s1, vec2 s2){
	vec2 result;
	result.x = s1.x + s2.x;
	result.y = s1.y + s2.y;
	return result;
}

vec2 substract(vec2 s1, vec2 s2){
	vec2 result;
	result.x = s1.x - s2.x;
	result.y = s1.y - s2.y;
	return result;
}

vec2 multiply(vec2 p1, vec2 p2) {
	vec2 result;
	result.x = p1.x*p2.x - p1.y*p2.y;
	result.y = p1.x*p2.y + p1.y*p2.x;
	return result;
}

vec2 divide2(vec2 d1, vec2 d2) {
	float divisor;
	divisor = pow(d2.x,2) + pow(d2.y,2);

	vec2 result;
	result.x = (d1.x*d2.x + d1.y*d2.y)/divisor;
	result.y = (-d1.x*d2.y + d1.y*d2.x)/divisor;
	return result;
}

vec2 divide(vec2 d1, vec2 d2) {
	vec2 result;
	result.x = -(d1.x*d2.x + d1.y*d2.y)/(pow(d2.x,2) + (pow(d2.y,2)));
	result.y = -(d1.x*d2.y + d1.y*d2.x)/(pow(d2.x,2) + (pow(d2.y,2)));
	return result;
}

vec2 power(vec2 base, float exponent) {
	vec2 polar; 
	polar.x = sqrt(pow(base.x,2) + pow(base.y,2));
	polar.y = atan(base.y/(base.x));
	polar.y *= exponent;
	polar.x = pow(polar.x, exponent);
	
	vec2 result;
	result.x = polar.x*cos(polar.y);
	result.y = polar.x*sin(polar.y);
	return result;
}

vec2 exp(vec2 exp) {
	vec2 result;
	result.x = pow(E, exp.x)*cos(exp.y);
	result.y = pow(E, exp.x)*sin(exp.y);
	return result;
}

vec2 tangens(vec2 z){
	vec2 result;
	result.x = sin(2*z.x)/(cos(2*z.x)+cosh(2*z.y));
	result.y = sinh(2*z.y)/(cos(2*z.x) + cosh(2*z.y));
	return result;

}

void main() {
	float zoom = scale;
	vec2 translate = vec2(v_scale.x,v_scale.y);
	f_color = v_color;
	vec2 C = vec2(v_position.x*zoom+translate.x, v_position.y*zoom+translate.y);

	//Julia
	vec2 Z = C;
	//Z.x = -0.221346489;
	//Z.y = 1.464902382;//-0.245608;


	int iteration = 0;
	
	//vec2 Z = C;
	//float real = 0;
	//float imaginar = 0;

	//float real

	while(iteration < MaxIteration) {
		//Mandelbrot
		//Z = add(multiply(Z,Z),C);
		//Z = add(power(Z,2), C);


		
		//Newtons Fractal
		vec2 divident = substract(exp(power(Z,3)) ,const_i);
		vec2 divisor = multiply(const_3, exp(power(Z,2)));
		Z = substract(Z, (divide2(divident,divisor)));

		//tangens
		//Z = add(multiply(Z, tangens(Z))  ,  multiply(const_i, C)); //Z*tan(Z)+i*c


		//own
		//Z = substract(Z, divide2(exp(power(Z,102)), multiply(const_3, exp(power(Z,105)))));
		

		//fractal2 geht nicht
		//vec2 divident = power(substract(Z,const_1),3);
		//vec2 divisor = multiply(const_3,power(Z,2));
		//Z = add(substract(Z, divide2(divident,divisor)), C);
		 

		//fractal 3
		//vec2 divident = add(power(Z,2), substract(C,const_1));
		//vec2 divisor = add(multiply(const_2, Z), substract(C,const_2));
		//Z = power(divide2(divident,divisor),0.5);
		
		if(pow(Z.x,2) + pow(Z.y,2) > 10000.0) {
			//RGB

			//f_color.r = 0.5 ;
			//f_color.r = 2*pow((iteration*2.0)/(MaxIteration+10),0.4);
			//f_color.g = 1.5*pow((iteration*2.1)/MaxIteration,0.3);
			//f_color.b = 0.2*pow((iteration*3.2)/(MaxIteration+100),0.5);

			//HSV
			float a = pow((iteration*1.0)/MaxIteration, 0.2);
			//vec3 RGB = hsvToRgb(vec3(-6*a+3.79,1.2-3*a,1));//3*a+0.5));
			//vec3 RGB = hsvToRgb(vec3(6*a+1.1,0.3*a+0.7,0.8));
			//vec3 RGB = hsvToRgb(vec3(15*a-1.7,0.9,1.2));
			//vec3 RGB = hsvToRgb(vec3(5.5*sin(3.2*a)-a*3.8+0.2,0.9-0.9*pow(a,2.3)*a,0.8*tan(2.4*a)-0.5)); //blue version
			vec3 RGB = hsvToRgb(vec3(
				a*1.0f+3.0f,
				0.5f*a*0.0f+1.0f-0.27f*a,
				-1.1f*a+8.0f
			));
			f_color.r = RGB.x;
			f_color.g = RGB.y;
			f_color.b = RGB.z;
		}
		//f_color.r = int(Z.x) % 124+0.5;
		iteration ++;
	}
	

	//v_color.r = a_position.y*0.5+0.5;
	//v_color.b = 0.5f;

}

