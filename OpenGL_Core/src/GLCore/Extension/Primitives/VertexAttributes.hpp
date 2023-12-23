#pragma once
#include <glad/glad.h>

namespace GLCore::Extension::Primitives {
	struct VertexAttribute {
		GLuint index;
		GLint size;
		GLenum type;
		GLboolean normalized;
		GLsizei stride;
		const void* pointer;

		VertexAttribute(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);
	};

	class VertexAttributes {
	private:

		std::vector<VertexAttribute*> vertexAttributes;
	public:
		VertexAttributes() = default;
		~VertexAttributes();

		void addVertexAttribute(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);
		void setAttributes();
		void enableAttributes();
		void disableAttributes();

		std::vector<VertexAttribute*>::iterator begin() { return vertexAttributes.begin(); }
		std::vector<VertexAttribute*>::iterator end() { return vertexAttributes.end(); }

	public:
		static inline std::shared_ptr<VertexAttributes> create() { 
			return std::make_shared<VertexAttributes>(); 
		}
	};
}