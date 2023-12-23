// Shader in takes an ArrayList of src and ShaderType
#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <unordered_map>

namespace GLCore::Extension::Shaders {
	struct PrimitiveShader {
		GLuint shaderID;
		GLenum SHADER_TYPE;
		std::string GLSL_PATH;
		std::string GLSL_SRC;

		PrimitiveShader(const GLenum& SHADER_TYPE, const std::string& GLSL_PATH);
		PrimitiveShader(const GLenum& SHADER_TYPE, const std::string& GLSL_PATH, const std::string& GLSL_SRC);
	};

	class Shader {
	private:
		std::string name;
		std::vector<PrimitiveShader*> PrimitiveShaders;
		std::unordered_map<std::string, int*> uniformLocations; //optimization
	protected:
		GLuint programID = 0;
		inline const GLuint& getProgramID() { return this->programID; }
	public:
		Shader(const std::string& name);
		virtual ~Shader();

		void addPrimitiveShader(PrimitiveShader* primitiveShader);

		void compile();
		void use();
		void detach();
		void destroy();

		inline const std::string& getName() { return this->name; }
	public:
		//The order you upload uniforms MATTER!! Make sure to upload .vert uniforms BEFORE .frag!!
		const int& getUniformLocation(const std::string& name);

		void uploadFloat(const std::string& name, const float& value);
		void uploadMat4f(const std::string& name, const glm::mat4& value);

		void uploadInt(const std::string& name, const int& value);
		void uploadTexture(const std::string& name, const unsigned int& slot);

	};
}