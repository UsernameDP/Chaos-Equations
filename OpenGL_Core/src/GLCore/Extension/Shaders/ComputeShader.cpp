#include "pch.hpp"
#include "ComputeShader.hpp"

namespace GLCore::Extension::Shaders {
	ComputeShader::ComputeShader(const std::string& name) : 
		Shader(name) {}

	ComputeShader::ComputeShader(const std::string& name, const std::string& computePath)
		: Shader(name) {
		addPrimitiveShader(new PrimitiveShader(GL_COMPUTE_SHADER, computePath));
	}

	void ComputeShader::dispatch(const glm::ivec3& dispatchDimensions, const GLbitfield& barrierMethod) {
		glDispatchCompute(dispatchDimensions.x, dispatchDimensions.y, dispatchDimensions.z);
		glMemoryBarrier(barrierMethod);
	}
}