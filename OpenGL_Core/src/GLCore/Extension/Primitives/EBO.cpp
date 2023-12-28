#include "pch.hpp"
#include "EBO.hpp"

namespace GLCore::Extension::Primitives
{
	EBO::EBO(const GLenum& DRAW_TYPE, std::vector<unsigned int> *indices) :
		GLBufferObject(GL_ELEMENT_ARRAY_BUFFER) {
		glGenBuffers(1, &ID);
		bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices->size() * sizeof(unsigned int), indices->data(), DRAW_TYPE);
		unbind();
	}

	void EBO::destroy()
	{
		glDeleteBuffers(GL_ELEMENT_ARRAY_BUFFER, &ID);
	}

	void EBO::updateData(std::vector<unsigned int>* data, const GLuint& offset_bytes) {
		bind();
		glBufferSubData(GL_ARRAY_BUFFER, offset_bytes, data->size() * sizeof(unsigned int), data->data());
		unbind();
	}

	void EBO::updateAndReallocateData(const GLenum& DRAW_TYPE, std::vector<unsigned int>* data){
		bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, data->size() * sizeof(unsigned int), data->data(), DRAW_TYPE);
		unbind();
	}
}