#pragma once


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "shader.h"
#include "vbo.h"
#include "vao.h"


namespace core
{

	class Renderer
	{
	public:
		Renderer();
		Renderer(const Renderer&) = delete;

		void render();

	private:
		std::vector<float> circleVertices;
		const int circleSmoothnes = 10;
		float radius = 0.015f;

		shader sh;
		VAO vao;
	};

}