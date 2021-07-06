#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cstdio>

class VBO
{
public:

	// GL_DYNAMIC_DRAW
	// GL_STATIC_DRAW
	// GL_STREAM_DRAW
	VBO(GLenum type);
	~VBO();
	void bind();
	void unbind();
	void buffer(const float* vertices, int size);

private:

	unsigned int handle;
	GLenum type;
};