#include "pch.hpp"
#include "SSBO.hpp"

namespace GLCore::Extension::Primitives {
	SSBO::SSBO(const GLenum& DRAW_TYPE, const GLuint& allocationSize_bytes)
		: GLBufferObject(GL_SHADER_STORAGE_BUFFER)
	{
		glGenBuffers(1, &ID);
		bind();
		glBufferData(GL_SHADER_STORAGE_BUFFER, allocationSize_bytes, nullptr, DRAW_TYPE);
		unbind();
	}
	void SSBO::bindAt(const GLuint& loc)
	{
		bind();
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, loc, ID);
	}

	void SSBO::unbind()
	{
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, ID);
	}

	void SSBO::destroy()
	{
		glDeleteBuffers(1, &ID);
	}
}