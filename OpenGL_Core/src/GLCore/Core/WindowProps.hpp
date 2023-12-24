#pragma once 
#include <glm/glm.hpp>

namespace GLCore {

	struct WindowProps {
		std::string name = "GLFW Window";
		glm::ivec2 dimensions = glm::ivec2(1280, 720);
		glm::ivec2 position = glm::ivec2(100, 100);
		glm::vec4 backgroundColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
		bool enableVsync = true;
		bool maximized = false;

		WindowProps() = default;
		WindowProps(std::string name, int width = 1280, int height = 720, const glm::vec4& backgroundColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

		inline int getWidth() { return this->dimensions.x; }
		inline int getHeight() { return this->dimensions.y; }
		inline int getPosX() { return this->position.x; }
		inline int getPosY() { return this->position.y; }

		inline void disableVsync() { enableVsync = false; }
		inline void maximize() { maximized = true; }
	};

}