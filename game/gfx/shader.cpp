#include "shader.h"

#pragma warning(disable:4996)
#pragma warning(disable:26451)

shader::shader()
	: vs_handle(0), fs_handle(0), handle(0)
{}

shader::shader(const char* vs_path, const char* fs_path)
{
	create(vs_path, fs_path);
}

int shader::create(const char* vs_path, const char* fs_path)
{
	printf("Creating shader\n");
	
    vs_handle = compile(vs_path, GL_VERTEX_SHADER);
	fs_handle = compile(fs_path, GL_FRAGMENT_SHADER);
	handle = glCreateProgram();
	assert((!vs_handle || !fs_handle || !handle) || "Shader creating error!");

    glAttachShader(handle, vs_handle);
    glAttachShader(handle, fs_handle);
    glLinkProgram(handle);

    GLint linked;
    glGetProgramiv(handle, GL_LINK_STATUS, &linked);
    assert(!(!linked && "Shader linking failed!"));

    glDeleteShader(vs_handle);
    glDeleteShader(fs_handle);
	printf("Shader successfuly created\n");

	return 0;
}

GLint shader::compile(const char* path, GLenum type)
{
    FILE* f;
    char* text;
    long len;

    f = fopen(path, "rb");
    if (f == NULL) {
        fprintf(stderr, "error loading shader at %s\n", path);
        exit(1);
    }

    fseek(f, 0, SEEK_END);
    len = ftell(f);
    assert(len > 0);
    fseek(f, 0, SEEK_SET);

    text = new char[len+1];
    fread(text, 1, len, f);
    text[len] = '\0';

    fclose(f);

    GLuint h_shader = glCreateShader(type);
    glShaderSource(h_shader, 1, (const GLchar* const*)&text, (const GLint*)&len);
    glCompileShader(h_shader);

    GLint compiled;
    glGetShaderiv(h_shader, GL_COMPILE_STATUS, &compiled);
    assert(!(!compiled && "Shader compilation error"));

    delete[] text;
    return h_shader;
}

void shader::use()
{
    glUseProgram(handle);
}

void shader::set_uniform(const std::string& name, glm::vec1 vec)
{
    glUniform1f(glGetUniformLocation(handle, name.c_str()), vec.x);
}

void shader::set_uniform(const std::string& name, glm::vec2 vec)
{
    glUniform2f(glGetUniformLocation(handle, name.c_str()), vec.x, vec.y);
}

void shader::set_uniform(const std::string& name, glm::vec3 vec)
{
    glUniform3f(glGetUniformLocation(handle, name.c_str()), vec.x, vec.y, vec.z);
}

void shader::set_uniform(const std::string& name, glm::vec4 vec)
{
    glUniform4f(glGetUniformLocation(handle, name.c_str()), vec.x, vec.y, vec.z, vec.w);
}

void shader::set_uniform(const std::string& name, glm::mat4 mat)
{
    glUniformMatrix4fv(glGetUniformLocation(handle, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}