#include "pch.hpp"
#include "VBO.hpp"

namespace GLCore::Extension::Primitives
{
	VBO::VBO(const GLenum& DRAW_TYPE, const GLuint& allocationSize_bytes) :
		GLBufferObject(GL_ARRAY_BUFFER) {

		glGenBuffers(1, &ID);
		bind();
		glBufferData(GL_ARRAY_BUFFER, allocationSize_bytes, nullptr, DRAW_TYPE);
	}

	void VBO::destroy()
	{
		glDeleteBuffers(GL_ARRAY_BUFFER, &ID);
	}
}