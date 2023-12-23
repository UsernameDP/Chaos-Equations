#include "pch.hpp"
#include "VAO.hpp"

namespace GLCore::Extension::Primitives {
	VAO::VAO() {
		glGenVertexArrays(1, &ID);
		bind();
	}

	void VAO::bind() {
		glBindVertexArray(ID);
	}
	void VAO::unbind() {
		glBindVertexArray(0);
	}

	void Primitives::VAO::destroy()
	{
		glDeleteVertexArrays(1, &ID);
	}
}