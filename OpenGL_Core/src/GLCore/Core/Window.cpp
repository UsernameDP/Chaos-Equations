#include "pch.hpp"
#include "GLCore/Core/Window.hpp"

#include "Application.hpp"

namespace GLCore
{
	static void INIT_GLFW()
	{
		if (!glfwInit())
		{
			LOG_ERROR("GLFW didn't initialize properly");
		}

		//Currently, we are using opengl 4.6
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef APPLE
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
		LOG_INFO("GLFW initialized");
	}
	static void INIT_GLAD()
	{
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			LOG_ERROR("Failed to initialize GLAD");
		}

		LOG_INFO("GLAD initialized");
	}
	
	//GLFW Callbacks
	void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
		Window::instance->props.dimensions.x = width;
		Window::instance->props.dimensions.y = height;
	}
	void Window::window_pos_callback(GLFWwindow* window, int xpos, int ypos) {
		Window::instance->props.position.x = xpos;
		Window::instance->props.position.y = ypos;
	}
	void Window::glfw_error_callback(int error, const char* description)
	{
		fprintf(stderr, "Error : %s\n", description);
	}

	Window* Window::instance = nullptr;

	Window::Window(const WindowProps& props){
		
		if (instance == nullptr) {
			Window::instance = this;
			this->props = props;

			INIT_GLFW();
			if (this->props.maximized) {
				glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);
			}
			glfwSetErrorCallback(Window::glfw_error_callback);

			GLFWWindow = glfwCreateWindow(this->props.getWidth(), this->props.getHeight(), this->props.name.c_str(), NULL, NULL);

			if (GLFWWindow == NULL)
			{
				LOG_ERROR("Failed to create GLFW window");
			}
			glfwMakeContextCurrent(GLFWWindow);

			if (this->props.enableVsync) {
				glfwSwapInterval(1);
			}

			INIT_GLAD();

			glViewport(0, 0, (int)this->props.dimensions.x, (int)this->props.dimensions.y);
			glfwSetFramebufferSizeCallback(GLFWWindow, Window::framebuffer_size_callback);
			glfwSetWindowPos(GLFWWindow, this->props.getPosX(), this->props.getPosY());
			glfwSetWindowPosCallback(GLFWWindow, Window::window_pos_callback);
		}
		else {
			LOG_ERROR("A Window instance already exists");
		}
	}

	Window::~Window()
	{
		glfwDestroyWindow(GLFWWindow);
		glfwTerminate();
	}

	void Window::onUpdate()
	{
		glfwPollEvents();
		glClearColor(props.backgroundColor.r, props.backgroundColor.g, props.backgroundColor.b, props.backgroundColor.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	const int Window::getGLSLVersion()
	{
		// Get the OpenGL version string
		const char *versionStr = reinterpret_cast<const char *>(glGetString(GL_VERSION));

		// Extract the major and minor version numbers from the version string
		int majorVersion = 0;
		int minorVersion = 0;

		std::stringstream versionStream(versionStr);
		versionStream >> majorVersion;
		versionStream.ignore(1); // Ignore the dot
		versionStream >> minorVersion;

		// Combine major and minor version to get the desired format (e.g., 3.3 or 330)
		int combinedVersion = majorVersion * 100 + minorVersion * 10;

		return combinedVersion;
	}

	const std::string Window::getGLSLVersionStr()
	{
		return "#version " + std::to_string(getGLSLVersion());
	}
}
