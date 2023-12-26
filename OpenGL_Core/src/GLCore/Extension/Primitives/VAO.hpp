#pragma once
#include "GLBindableInterface.hpp"

namespace GLCore::Extension::Primitives {
	class VAO : public GLBindableInterface {
	private:
		std::vector<unsigned int> attributes;
		bool attributesEnabled = true;
	public:
		VAO();
		virtual ~VAO() override;

		void bind() override;
		void unbind() override;
		void destroy() override;

		void addVertexAttributeFloat(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer); //for vec2, vec3, vec4, ...
		void addVertexAttributeInt(GLuint index, GLint size, GLenum type, GLsizei stride, const void* pointer); //for ivec2, ivec3, uint, int, ...

		void enableAttributes();
		void disableAttributes();
	};
}