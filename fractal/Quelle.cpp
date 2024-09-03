#include <iostream>c
#define GLEW_STATIC
#include <GL/glew.h>
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <windows.h>
#include <math.h>


#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")

#include "defines.h";
#include "vertex_buffer.h";
#include "shader.h";
#include "BigInt.hpp";
//#include "vec2.h";
#include <vector>


/*vec2 power(vec2 base, float exponent) {
	vec2 polar;
	polar.x = sqrt(pow(base.x, 2) + pow(base.y, 2));
	polar.y = atan(base.y / base.x);

	polar.y *= exponent;
	polar.x = pow(polar.x, exponent);

	vec2 result;
	result.x = polar.x * cos(polar.y);
	result.y = polar.x * sin(polar.y);
	return result;
}*/

void power(float baseX, float baseY, float exponent) {
	float polarX = sqrt(pow(baseX, 2) + pow(baseY, 2));
	float polarY = atan(baseY / baseX);

	polarY *= exponent;
	polarX = pow(polarX, exponent);

	float resultX = polarX * cos(polarY);
	float resultY = polarX * sin(polarY);

	//std::cout << resultX << " " << resultY;
}

float mod(float a, float b) {
	return a - (b * floor(a / b));
}


int main(int argc, char** argv) {


	SDL_Window* window;
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	uint32 flags = SDL_WINDOW_OPENGL;
	float32 width = 800;
	float32 height = 800;

	window = SDL_CreateWindow("C++ Fraktal", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
	SDL_GLContext glContext = SDL_GL_CreateContext(window);

	GLenum err = glewInit();
	if (err != GLEW_OK) {
		std::cout << "Error: " << glewGetErrorString(err) << std::endl;
		std::cin.get();
		return -1;
	}
	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

	float32 translateX = 0.2;
	float32 translateY = 0.4;
	float32 scaleBase = 0.9;
	float32 scaleExp = 0.0;
	float32 factorScale = 0.9;


	Vertex vertices[] = {
		Vertex{-1.0f, -1.0f, 0.0f,
		1.0f, 0.0f, 0.0f, 1.0f},
		Vertex{-1.0f, 1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f, 1.0f},
		Vertex{1.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 1.0f},
		Vertex{-1.0f, -1.0f, 0.0f,
		1.0f, 0.0f, 0.0f, 1.0f},
		Vertex{1.0f, -1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f, 1.0f},
		Vertex{1.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 1.0f}
	};
	uint32 numVertices = 6;

	VertexBuffer vertexBuffer(vertices, numVertices);
	vertexBuffer.unBind();

	Shader shader("shaders/basic.vs", "shaders/basic.fs");
	shader.bind();

	int scaleUniformLocation = glGetUniformLocation(shader.getShaderId(), "v_scale");
	if (scaleUniformLocation != -1) {
		glUniform4f(scaleUniformLocation, translateX, translateY, scaleBase, scaleExp);
	}

	bool close = false;
	bool zoomOut = false;
	float speedZoom = 0.01;
	scaleExp = 25;
	

	power(0.01, 0.02, 2);

	//std::cout << mod(0.0353, 100.0)/100;

	while (!close) {
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//X: 1.00671 Y: 0.581223
		//translateX = 1.00671;//1.2384;
		//translateX = 1.2384;
		//translateY = 0.581223; //0.96;
		//translateY = 0.96;

		//translateX = -0.37044;
		//translateY = -0.64908;
		//translateX = -0.911137;
		//translateY = -0.582273;

		//translateX = -0.221346489;//-1.39448;
		//translateY = 1.464902382;//-0.245608;

		translateX = -1.37477;
		translateY = -0.244335;

		if (zoomOut) {
			scaleExp += speedZoom;
		}

		if (scaleUniformLocation != -1) {
			glUniform4f(scaleUniformLocation, translateX, translateY, scaleBase, scaleExp);
		}

		vertexBuffer.bind();
		glDrawArrays(GL_TRIANGLES, 0, numVertices);
		vertexBuffer.unBind();

		SDL_GL_SwapWindow(window);

		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				close = true;
			}
			
			if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.sym)
				{
				case SDLK_RIGHT:
					translateX += 0.1* pow(scaleBase, scaleExp);
					break;
				case SDLK_LEFT:
					translateX -= 0.1* pow(scaleBase, scaleExp);
					break;
				case SDLK_UP:
					translateY += 0.1* pow(scaleBase, scaleExp);
					break;
				case SDLK_DOWN:
					translateY -= 0.1* pow(scaleBase, scaleExp);
					break;
				case SDLK_0:
					zoomOut = !zoomOut;
					break;
				case SDLK_9:
					speedZoom *= 10.0;
					break;
				case SDLK_8:
					speedZoom *= 0.1;
					break;
				case SDLK_1:
					std::cout << "X: " << translateX << " Y: " << translateY << '\n';
				default:
					break;
				}
			}
			if (event.type == SDL_MOUSEWHEEL) {
				if (event.wheel.y != 0) {
					
					float32 Mx = 2*event.wheel.mouseX / (width)-1;
					float32 My = 2*event.wheel.mouseY / (height)-1;
					float32 w = 2 * pow(scaleBase, scaleExp);
					float32 s = factorScale;
					float32 ratioX = (Mx + 1) / 2;
					float32 ratioY = (My + 1) / 2;

					translateX += w * s / 2 + ratioX * w - ratioX * w * s - pow(scaleBase, scaleExp);
					translateY -= w * s / 2 + ratioY * w - ratioY * w * s - pow(scaleBase, scaleExp);

					//std::cout << scaleExp << '\n';

					scaleExp += event.wheel.y;
				}
			}
		}
		//scale *= 0.9999;

	}
	return 0;
}