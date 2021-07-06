#include "../../state.h"
#include "renderer.h"

const float STICK_WIDTH = 0.1f;
//const float STICK_WIDTH = 100.0f;
const float STICK_HEIGHT = 2 * STICK_WIDTH;

core::Renderer::Renderer()
{
	sh.create("game/res/shaders/basic.vs", "game/res/shaders/basic.fs");

	/*float vertices[] = {
		 STICK_WIDTH / 2,  STICK_HEIGHT / 2,  0.0f, 0.0f, 0.0f,
		 STICK_WIDTH / 2, -STICK_HEIGHT / 2,  0.0f, 0.0f, 0.0f,
		-STICK_WIDTH / 2, -STICK_HEIGHT / 2,  0.0f, 0.0f, 0.0f,

		-STICK_WIDTH / 2, -STICK_HEIGHT / 2,  0.2f, 0.2f, 0.2f,
		 STICK_WIDTH / 2,  STICK_HEIGHT / 2,  0.2f, 0.2f, 0.2f,
		-STICK_WIDTH / 2,  STICK_HEIGHT / 2,  0.2f, 0.2f, 0.2f,
	};*/


	circleVertices.push_back(0.0f);
	circleVertices.push_back(0.0f);
	circleVertices.push_back(0.0f);
	circleVertices.push_back(0.0f);
	circleVertices.push_back(0.0f);

	

	for (int i = 0; i <= circleSmoothnes; i++)
	{
		float x = cos(glm::radians((360.0f / circleSmoothnes) * i));
		float y = sin(glm::radians((360.0f / circleSmoothnes) * i));

		circleVertices.push_back(x * radius);
		circleVertices.push_back(y * radius);
		circleVertices.push_back(0.0f);
		circleVertices.push_back(0.0f);
		circleVertices.push_back(0.0f);
	}

	VBO vbo(GL_STATIC_DRAW);
	//vbo.buffer(vertices, sizeof(vertices));
	vbo.buffer(circleVertices.data(), circleVertices.size() * sizeof(float));

	vao.create();
	vao.bind();

	vao.set_attr(0, 2, GL_FLOAT, 5 * sizeof(float), 0);
	vao.set_attr(1, 3, GL_FLOAT, 5 * sizeof(float), 2 * sizeof(float));
	vbo.unbind();
}

void core::Renderer::render()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	sh.use();

	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 proj = glm::mat4(1.0f);

	//proj = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f);
	proj = glm::ortho<float>(-window->orthoX, window->orthoX, -window->orthoY, window->orthoY);

	sh.set_uniform("view", view);
	sh.set_uniform("proj", proj);

	vao.bind();

	glm::mat4 model = glm::mat4(1.0f);
	sh.set_uniform("model", model);
	//glEnable(GL_MULTISAMPLE);
	glDrawArrays(GL_TRIANGLE_FAN, 0, circleSmoothnes+2);

	//model = glm::translate(model, glm::vec3(0.035f, 0, 0));

	//sh.set_uniform("view", view);
	//sh.set_uniform("proj", proj);
	//sh.set_uniform("model", model);
	//glDisable(GL_MULTISAMPLE);
	//glDrawArrays(GL_TRIANGLE_FAN, 0, circleSmoothnes + 2);


	//for (int i = 0; i < logic->board.heap.size(); i++)
	//{
	//	if (logic->board.heap[i]->relation == 0)
	//	{
	//		glm::mat4 model = glm::mat4(1.0f);
	//		//model = glm::translate(model, glm::vec3(STICK_HEIGHT * (logic->board.heap[i]->pos), 0.0f, 0.0f));
	//		//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	//		sh.set_uniform("model", model);
	//		glDrawArrays(GL_TRIANGLES, 0, 6);
	//	}
	//}
}
