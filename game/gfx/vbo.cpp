#include "vbo.h"

VBO::VBO(GLenum t)
	:type(t)
{
	glGenBuffers(1, &handle);
	printf("vbo created\n");
}

VBO::~VBO()
{
	//glDeleteBuffers(1, &handle);
	
}

void VBO::unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, handle);
}

void VBO::buffer(const float* vertices, int size)
{
	bind();
	glBufferData(GL_ARRAY_BUFFER, size, vertices, type);
}
