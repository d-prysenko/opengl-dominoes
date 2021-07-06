#pragma once


#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <thread>
#include <chrono>


namespace core
{

	class Window
	{
	public:

		bool isWindowShuldClose = false;
		int width, height;
		GLfloat orthoX, orthoY;

		Window();
		Window(int width, int height);
		~Window();

		int window_create(int width, int height);
		void end_scene();

	private:

		GLFWwindow* window;
		
		static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void close_callback(GLFWwindow* window);
	};

}