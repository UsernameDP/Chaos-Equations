#include "pch.hpp"
#include "EBO.hpp"

namespace GLCore::Extension::Primitives
{
	EBO::EBO(std::vector<unsigned int> *indices) : 
		GLBufferObject(GL_ELEMENT_ARRAY_BUFFER) {
		glGenBuffers(1, &ID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices->size() * sizeof(unsigned int), indices->data(), GL_STATIC_DRAW);
	}

	void EBO::destroy()
	{
		glDeleteBuffers(GL_ELEMENT_ARRAY_BUFFER, &ID);
	}
}