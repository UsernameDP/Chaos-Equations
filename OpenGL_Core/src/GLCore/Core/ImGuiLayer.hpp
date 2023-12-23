#pragma once
#include "Layer.hpp"
#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <imgui.h>

namespace GLCore {

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void onAttach() override;
		virtual void onDetach() override;

		void begin();
		void end();
	};

}