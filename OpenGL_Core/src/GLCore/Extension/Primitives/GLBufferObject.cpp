#include "pch.hpp"
#include "GLBufferObject.hpp"

namespace GLCore::Extension::Primitives {
	GLBufferObject::GLBufferObject(const GLenum& type) : type(type){}

	GLBufferObject::~GLBufferObject()
	{
		unbind();
		destroy();
	}

	void GLBufferObject::bind()
	{
		glBindBuffer(this->type, this->ID);
	}

	void GLBufferObject::unbind()
	{
		glBindBuffer(this->type, 0);
	}
}