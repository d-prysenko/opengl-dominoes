#include "vao.h"

VAO::VAO()
	: handle(0), _vbo(0)
{}

VAO::~VAO()
{
	//glDeleteVertexArrays(1, &handle);
}

void VAO::create()
{
	glGenVertexArrays(1, &handle);
}

void VAO::bind()
{
	glBindVertexArray(handle);
}

void VAO::set_attr(GLuint index, GLint size, GLenum type, GLsizei stride, size_t offset)
{
	glVertexAttribPointer(index, size, type, GL_FALSE, stride, (void*)offset);
	glEnableVertexAttribArray(index);
}