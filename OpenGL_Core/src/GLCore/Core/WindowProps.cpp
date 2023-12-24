#include "pch.hpp"
#include "WindowProps.hpp"

namespace GLCore {

	WindowProps::WindowProps(std::string name, int width, int height, const glm::vec4& backgroundColor) {
		this->name = name;
		this->dimensions.x = width;
		this->dimensions.y = height;
		this->backgroundColor = backgroundColor;
	}
}