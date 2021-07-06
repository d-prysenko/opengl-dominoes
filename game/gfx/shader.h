#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <stdio.h>
#include <cassert>


class shader
{
public:
	shader();
	shader(const char* vs_path, const char* fs_path);

	int create(const char* vs_path, const char* fs_path);
	void use();
	void set_uniform(const std::string& name, glm::vec1 vec);
	void set_uniform(const std::string& name, glm::vec2 vec);
	void set_uniform(const std::string& name, glm::vec3 vec);
	void set_uniform(const std::string& name, glm::vec4 vec);
	void set_uniform(const std::string& name, glm::mat4 vec);

private:
	unsigned int handle, vs_handle, fs_handle;

	GLint compile(const char* path, GLenum type);
};

