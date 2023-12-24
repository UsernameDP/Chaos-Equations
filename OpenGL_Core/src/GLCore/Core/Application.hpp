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
		Application(const WindowProps& props);
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