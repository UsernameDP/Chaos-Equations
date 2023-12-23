#pragma once
#include "../Extension.hpp"
#include "Shader.hpp"

namespace GLCore::Extension::Shaders {
	class VertexPipelineShader : public Shader {
	public:
		VertexPipelineShader() = default;
		VertexPipelineShader(const std::string& name, const std::string& vertPath, const std::string& fragPath);
	};
}