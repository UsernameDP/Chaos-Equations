#include "pch.hpp"
#include "Application.hpp"

#include "GLCore/Extension/AssetPool.hpp"
#include "OpenGLDebug.hpp"

namespace GLCore
{

	Application *Application::instance = nullptr;

	Application::Application(const std::string &name,
							 uint32_t width,
							 uint32_t height,
							 const glm::vec4 &backgroundColor)
	{
		if (instance == nullptr)
		{
			GLCore::Log::init();
			GLCore::Extension::AssetPool::init();

			Application::instance = this;
		}
		else
		{
			LOG_WARN("Application instance already exists");
		}

		this->layers = std::make_unique<LayerStack>();

		WindowProps props = WindowProps(name, width, height, backgroundColor);
		this->window = std::make_unique<Window>(props);
		this->window->init();

		imguiLayer = new ImGuiLayer();
		pushLayerFront(imguiLayer);

#ifdef DEBUG
		setGLDebugLogLevel(DebugLogLevel::HighAssert);
#else
		setGLDebugLogLevel(DebugLogLevel::None);
#endif
		enableGLDebugging();
	}

	void Application::run()
	{
		if (window == nullptr)
		{
			LOG_ERROR("Application's window is not set!!");
		}

		float currentTime;

		TimeStep timeStep;

		while (window->running())
		{
			currentTime = (float)glfwGetTime();
			timeStep.setTime(currentTime);
			window->onUpdate();

			for (Layer *layer : *layers)
			{
				layer->onUpdate(timeStep);
			}

			imguiLayer->begin();
			for (Layer *layer : *layers)
			{
				layer->onImguiUpdate(timeStep);
			}
			imguiLayer->end();

			glfwSwapBuffers(window->getGLFWWindow());
		}
	}

	bool Application::getKeyPressed(uint16_t GLFW_KEY)
	{
		return ImGui::GetIO().KeysDown[GLFW_KEY];
	}
	bool Application::isImGuiFocused(ImGuiFocusedFlags flag)
	{
		return ImGui::IsWindowFocused(flag);
	}
}