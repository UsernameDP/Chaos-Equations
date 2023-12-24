#pragma once
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace GLCore {
	struct WindowProps {
		std::string name;
		uint32_t width;
		uint32_t height;
		glm::vec4 backgroundColor;

		WindowProps( const std::string& name,
			uint32_t width, 
			uint32_t height,
			const glm::vec4& backgroundColor
		);
	};

	class Window {
	private:
		WindowProps props; 
		GLFWwindow* GLFWWindow;
	private:
		static bool enableVsync;
	public:
		Window(const WindowProps& props);
		~Window();

		void init();
		void onUpdate();

		const int getGLSLVersion();
		const std::string getGLSLVersionStr();
		inline bool running() { return !glfwWindowShouldClose(GLFWWindow); }
		inline GLFWwindow* getGLFWWindow() { return GLFWWindow; }
		inline const std::string& getName() { return props.name; }
		inline const uint32_t& getWidth() { return props.width; }
		inline const uint32_t& getHeight() { return props.height; }
	public:
		inline static void disableVsync() { Window::enableVsync = false; }
		inline static bool isVsyncEnabled() { return Window::enableVsync; }
	};
}