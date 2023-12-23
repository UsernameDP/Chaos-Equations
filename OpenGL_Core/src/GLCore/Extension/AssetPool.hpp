#pragma once
#include "Shaders/Shader.hpp"
#include "Shaders/ComputeShader.hpp"

namespace GLCore::Extension {

	class AssetPool {
	private:
		static std::unique_ptr<AssetPool> instance;
	public:
		AssetPool() = default;
		~AssetPool();

	private:
		std::unordered_map<std::string, std::string*> GLSL_SRCS;
		std::unordered_map<std::string, Shaders::Shader*> shaders;
		std::unordered_map<std::string, Shaders::ComputeShader*> computeShaders;
	public:
		static void init();
	public:
		static std::string& getGLSL_SRC(const std::string& relativePath);
		
		static Shaders::Shader& getShader(const std::string& name);
		static void setShader(Shaders::Shader* shader);

		static Shaders::ComputeShader& getComputeShader(const std::string& name);
		static void setComputeShader( Shaders::ComputeShader* shader );

	};

}