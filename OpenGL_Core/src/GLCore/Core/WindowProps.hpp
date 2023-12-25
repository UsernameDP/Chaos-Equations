#pragma once 
#include <glm/glm.hpp>
#include "imgui.h"

namespace GLCore {

	struct WindowProps {
		std::string name = "GLFW Window";
		glm::ivec2 dimensions = glm::ivec2(1280, 720);
		glm::ivec2 position = glm::ivec2(100, 100);
		
		glm::vec2 scroll = glm::vec2(0, 0); //relative position

		glm::vec4 backgroundColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
		bool enableVsync = true;
		bool maximized = false;

		WindowProps() = default;
		WindowProps(std::string name, int width = 1280, int height = 720, const glm::vec4& backgroundColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

		inline int getWidth() { return this->dimensions.x; }
		inline int getHeight() { return this->dimensions.y; }
		inline int getPosX() { return this->position.x; }
		inline int getPosY() { return this->position.y; }

		//Window callbacks already supplied by ImGui
		inline float getMousePosX() { return ImGui::GetIO().MousePos.x; }
		inline float getMousePosY() { return ImGui::GetIO().MousePos.y; }
		inline float getMousePosDeltaX() { return ImGui::GetIO().MouseDelta.x; }
		inline float getMousePosDeltaY() { return ImGui::GetIO().MouseDelta.y; }
		inline bool getKeyPressed(uint16_t GLFW_KEY) { return ImGui::GetIO().KeysDown[GLFW_KEY]; }
		inline bool getRightMouseDown() { return ImGui::GetIO().MouseDown[1]; }
		inline float getScrollY() { return scroll.y; }

		inline void disableVsync() { enableVsync = false; }
		inline void maximize() { maximized = true; }
	};

}