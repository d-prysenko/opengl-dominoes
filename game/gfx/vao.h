#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class VAO
{
public:
	
	VAO();
	~VAO();

	void bind();
	void create();
	void set_attr(GLuint index, GLint size, GLenum type, GLsizei stride, size_t offset);

private:
	unsigned int handle;

	unsigned int _vbo;
};

