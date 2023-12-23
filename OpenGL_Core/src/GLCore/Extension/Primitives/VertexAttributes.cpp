#include "pch.hpp"
#include "VertexAttributes.hpp"

namespace GLCore::Extension::Primitives {
	VertexAttribute::VertexAttribute(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer) : 
		index(index), 
		size(size), 
		type(type), 
		normalized(normalized), 
		stride(stride), 
		pointer(pointer) {}


	VertexAttributes::~VertexAttributes() {
		for (VertexAttribute* attribute : vertexAttributes) {
			delete attribute;
		}
	}


	void VertexAttributes::addVertexAttribute(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer)
	{
		vertexAttributes.push_back(new VertexAttribute(index, size, type, normalized, stride, pointer));
	}

	void VertexAttributes::setAttributes() {
		for (VertexAttribute* attribute : vertexAttributes) {
			glVertexAttribPointer(
				attribute->index,
				attribute->size,
				attribute->type,
				attribute->normalized,
				attribute->stride,
				attribute->pointer);
			glEnableVertexAttribArray(attribute->index);
		}
		disableAttributes();
	}
	void VertexAttributes::enableAttributes() {
		for (VertexAttribute* attribute : vertexAttributes) {
			glEnableVertexAttribArray(attribute->index);
		}
	}
	void VertexAttributes::disableAttributes() {
		for (VertexAttribute* attribute : vertexAttributes) {
			glDisableVertexAttribArray(attribute->index);
		}
	}
}