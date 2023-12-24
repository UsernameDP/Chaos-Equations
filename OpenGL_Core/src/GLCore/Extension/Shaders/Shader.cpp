#include "pch.hpp"
#include "Shader.hpp"
#include "GLCore/Extension/AssetPool.hpp"

namespace GLCore::Extension::Shaders
{
	static void checkShaderSuccess(const std::string& shaderPath, GLuint& shaderID) {
		int  success;
		char infoLog[512];
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shaderID, 512, NULL, infoLog);
			std::string message = "SHADER COMPILATION FAILED " + shaderPath + "\n" +
				"InfoLog : " + infoLog;

			LOG_ERROR(message);
		}
	}
	static void checkProgramSuccess(GLuint& programID) {
		int  success;
		char infoLog[512];
		glGetProgramiv(programID, GL_LINK_STATUS, &success);

		if (!success) {
			glGetProgramInfoLog(programID, 512, NULL, infoLog);
			std::string message = std::string("SHADER_PROGRAM LINKING FAILED ") + "\n" +
				"InfoLog : " + infoLog;

			LOG_ERROR(message);
		}
	}

	PrimitiveShader::PrimitiveShader(const GLenum &SHADER_TYPE, const std::string &GLSL_PATH) 
		: shaderID(0)
	{
		this->SHADER_TYPE = SHADER_TYPE;
		this->GLSL_PATH = GLSL_PATH;
		this->GLSL_SRC = AssetPool::getGLSL_SRC(GLSL_PATH);
	};
	PrimitiveShader::PrimitiveShader(const GLenum& SHADER_TYPE, const std::string& GLSL_PATH, const std::string& GLSL_SRC) {
		this->SHADER_TYPE = SHADER_TYPE;
		this->GLSL_PATH = GLSL_PATH;
		this->GLSL_SRC = GLSL_SRC;
	}

	Shader::Shader(const std::string &name) : name(name){};
	Shader::~Shader()
	{
		detach();
		destroy();
		for (PrimitiveShader *p : PrimitiveShaders)
		{
			delete p;
		}
		PrimitiveShaders.clear();

		for	(auto& pair : uniformLocations) {
			delete pair.second;
		}
		uniformLocations.clear();
	}

	void Shader::addPrimitiveShader(PrimitiveShader* primitiveShader)
	{
		PrimitiveShaders.push_back(primitiveShader);
	}

	void Shader::compile()
	{
		// Compile PrimitiveShaders
		for (PrimitiveShader *p : PrimitiveShaders)
		{
			const char *SHADER_SRC_C = p->GLSL_SRC.c_str();

			if (p->GLSL_SRC.empty())
				LOG_ERROR("{0} is empty", p->GLSL_PATH);

			p->shaderID = glCreateShader(p->SHADER_TYPE);
			glShaderSource(p->shaderID, 1, &SHADER_SRC_C, NULL);
			glCompileShader(p->shaderID);
			checkShaderSuccess(p->GLSL_PATH, p->shaderID);
		}

		// Link Program
		programID = glCreateProgram();
		for (PrimitiveShader *p : PrimitiveShaders)
		{
			glAttachShader(programID, p->shaderID);
		}
		glLinkProgram(programID);
		checkProgramSuccess(programID);

		// Delete PrimitiveShader IDS
		for (PrimitiveShader *p : PrimitiveShaders)
		{
			glDeleteShader(p->shaderID);
		}
	}
	void Shader::use()
	{
		glUseProgram(programID);
	}
	void Shader::detach()
	{
		glUseProgram(0);
	}
	void Shader::destroy()
	{
		glDeleteProgram(programID);
	}

	/*All uniform uploads*/
	const int& Shader::getUniformLocation(const std::string &name)
	{
		if (uniformLocations[name] == nullptr) {
			int location = glGetUniformLocation(programID, name.c_str());
			if (location == -1)
			{ // location = -1 if the "name" uniform is never mentioned in main
				LOG_WARN("{0} doesn't exist! Program will run without uniform", name);
			}
			uniformLocations[name] = new int(location);
		}

		return *uniformLocations[name];
	}

	// Floats
	void Shader::uploadFloat(const std::string &name, const float &value)
	{
		glUniform1f(getUniformLocation(name), value);
	}
	void Shader::uploadMat4f(const std::string &name, const glm::mat4 &value)
	{
		glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &value[0][0]);
	}
	void Shader::uploadVec2f(const std::string& name, const glm::vec2& value) {
		glUniform2f(getUniformLocation(name), value.x, value.y);
	}
	void Shader::uploadVec3f(const std::string& name, const glm::vec3& value) {
		glUniform3f(getUniformLocation(name), value.x, value.y, value.z);
	}
	void Shader::uploadVec4f(const std::string& name, const glm::vec4& value) {
		glUniform4f(getUniformLocation(name), value.r, value.g, value.b, value.a);
	}

	// Ints
	void Shader::uploadInt(const std::string &name, const int &value)
	{
		glUniform1i(getUniformLocation(name), value);
	}
	void Shader::uploadTexture(const std::string& name, const unsigned int& slot)
	{
		glUniform1i(getUniformLocation(name), slot);
	}
	void Shader::uploadUnsignedInt(const std::string& name, const unsigned int& value)
	{
		glUniform1ui(getUniformLocation(name), value);
	}
}