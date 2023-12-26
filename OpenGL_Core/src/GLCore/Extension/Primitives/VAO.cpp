#include "pch.hpp"
#include "VAO.hpp"

namespace GLCore::Extension::Primitives {
	VAO::VAO() : GLBindableInterface() {
		glGenVertexArrays(1, &ID);
		bind();
	}
	VAO::~VAO() {
		unbind();
		destroy();
	}

	void VAO::bind() {
		glBindVertexArray(ID);
		enableAttributes();
	}
	void VAO::unbind() {
		disableAttributes();
		glBindVertexArray(0);
	}
	void Primitives::VAO::destroy()
	{
		glDeleteVertexArrays(1, &ID);
	}
	void VAO::addVertexAttributeFloat(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer)
	{
		glVertexAttribPointer(index, size, type, normalized, stride, pointer);
		glEnableVertexAttribArray(index);
		attributes.push_back(index);
	}
	void VAO::addVertexAttributeInt(GLuint index, GLint size, GLenum type, GLsizei stride, const void* pointer)
	{
		glVertexAttribIPointer(index, size, type, stride, pointer);
		glEnableVertexAttribArray(index);
		attributes.push_back(index);
	}
	void VAO::enableAttributes()
	{
		for (const unsigned int& attribute : attributes)
			glEnableVertexAttribArray(attribute);
		attributesEnabled = true;
	}
	void VAO::disableAttributes()
	{
		if (attributesEnabled) {
			for (const unsigned int& attribute : attributes)
				glDisableVertexAttribArray(attribute);
			attributesEnabled = false;
		}
	}
}