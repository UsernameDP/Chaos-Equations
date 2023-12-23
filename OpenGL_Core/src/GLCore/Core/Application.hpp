#pragma once
#include "Window.hpp"
#include "LayerStack.hpp"
#include "ImGuiLayer.hpp"


namespace GLCore
{
	class Application
	{
	private:
		static Application *instance;

	private:
		std::unique_ptr<Window> window;
		std::unique_ptr<LayerStack> layers;
		ImGuiLayer* imguiLayer;

	public:
		Application(const std::string& name = "GLFW Window",
			uint32_t width = 1280,
			uint32_t height = 720,
			const glm::vec4& backgroundColor = glm::vec4(0.0, 0.0, 0.0, 1.0));
		virtual ~Application() = default;
		virtual void init() = 0;
		virtual void run();

		inline void pushLayer(Layer* layer) { this->layers->pushLayer(layer); }
		inline void pushLayerFront(Layer* layer) { this->layers->pushLayerFront(layer); }

	public:
		inline Window& getWindow() { return *(this->window); }
		bool getKeyPressed(uint16_t GLFW_KEY);
		bool isImGuiFocused(ImGuiFocusedFlags flag = ImGuiFocusedFlags_AnyWindow);

	public:
		static inline Application& get() { return *Application::instance; }
	};

}