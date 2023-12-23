#include "pch.hpp"
#include "AssetPool.hpp"
#include "GLCore/util/FileHandler.hpp"

namespace GLCore::Extension {

	std::unique_ptr<AssetPool> AssetPool::instance = nullptr;

	AssetPool::~AssetPool() {
		for (auto& pair : AssetPool::GLSL_SRCS) {
			delete pair.second;
		}
		AssetPool::GLSL_SRCS.clear();
		for (auto& pair : AssetPool::shaders) {
			delete pair.second;
		}
		AssetPool::shaders.clear();
		for (auto& pair : AssetPool::computeShaders) {
			delete pair.second;
		}
		AssetPool::computeShaders.clear();
	}

	void AssetPool::init() {
		if (instance == nullptr) {
			instance = std::make_unique<AssetPool>();
		}
		else {
			LOG_WARN("AssetPool instance already exists");
		}
	}

	std::string& AssetPool::getGLSL_SRC(const std::string& relativePath) {
		
		if (AssetPool::instance->GLSL_SRCS[relativePath] == nullptr) {
			std::string absPath = ASSETS_PATH + relativePath;
			std::string GLSL = util::FileHandler::readFile(absPath);
			AssetPool::instance->GLSL_SRCS[relativePath] = new std::string(GLSL);
		}

		return *(AssetPool::instance->GLSL_SRCS[relativePath]);
	}
	Shaders::Shader& AssetPool::getShader(const std::string& name)
	{
		Shaders::Shader* shader = AssetPool::instance->shaders[name];
		if (shader == nullptr) {
			LOG_ERROR("{0} shader needs to be set before", name);
		}

		return *shader;
	}
	void AssetPool::setShader(Shaders::Shader* shader)
	{
		if (shader == nullptr) {
			LOG_ERROR("You are setting a nullptr shader");
		}
		else {
			shader->compile();
			AssetPool::instance->shaders[shader->getName()] = shader;
		}
	}
	Shaders::ComputeShader& AssetPool::getComputeShader(const std::string& name)
	{
		if (AssetPool::instance->computeShaders[name] == nullptr) {
			LOG_ERROR("{0} shader needs to be set before", name);
		}

		return *AssetPool::instance->computeShaders[name];
	}
	void AssetPool::setComputeShader(Shaders::ComputeShader* shader)
	{
		shader->compile();
		AssetPool::instance->computeShaders[shader->getName()] = shader;
	}
}