#pragma once
#include "WindowProps.hpp"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace GLCore {

	class Window {
	private:
		static Window* instance;
	private:
		WindowProps props;
		GLFWwindow* GLFWWindow = nullptr;
	public:
		Window(const WindowProps& props);
		~Window();

		void onUpdate();

		const int getGLSLVersion();
		const std::string getGLSLVersionStr();
		inline bool running() { return !glfwWindowShouldClose(GLFWWindow); }
		inline GLFWwindow* getGLFWWindow() { return GLFWWindow; }
		inline WindowProps& getProps() { return props; }
	
	private:
		//static GLFW Callbacks
		static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
		static void window_pos_callback(GLFWwindow* window, int xpos, int ypos);
		static void glfw_error_callback(int error, const char* description);
		static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	};
}