#include <iostream>c
#define GLEW_STATIC
#include <GL/glew.h>
#define SDL_MAIN_HANDLED
#include <SDL.h>

#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")

#include "defines.h";
#include "vertex_buffer.h";
#include "shader.h";

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


	window = SDL_CreateWindow("C++ Fraktal", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, flags);
	SDL_GLContext glContext = SDL_GL_CreateContext(window);

	GLenum err = glewInit();
	if (err != GLEW_OK) {
		std::cout << "Error: " << glewGetErrorString(err) << std::endl;
		std::cin.get();
		return -1;
	}
	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

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

	bool close = false;
	while (!close) {
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		vertexBuffer.bind();
		glDrawArrays(GL_TRIANGLES, 0, numVertices);
		vertexBuffer.unBind();

		SDL_GL_SwapWindow(window);

		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				close = true;
			}
		}
	}

	return 0;
}