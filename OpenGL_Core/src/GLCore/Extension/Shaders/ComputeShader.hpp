#pragma once
#include "Shader.hpp"

namespace GLCore::Extension::Shaders {
	class ComputeShader : public Shader {
	public:
		ComputeShader(const std::string& name);
		ComputeShader(const std::string& name, const std::string& computePath);
	public:
		void dispatch(const glm::ivec3& dispatchDimensions, const GLbitfield& barrierMethod = GL_ALL_BARRIER_BITS);
	};
}