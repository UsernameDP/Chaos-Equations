#pragma once
#include "GLBufferObject.hpp"

namespace GLCore::Extension::Primitives {
	class VBO : public GLBufferObject {
	private:
	public:
		template<typename T>
		VBO(const GLenum& DRAW_TYPE,
			std::vector<T>* vertexData
		) : GLBufferObject(GL_ARRAY_BUFFER) {
			glGenBuffers(1, &ID);
			bind();
			glBufferData(GL_ARRAY_BUFFER, vertexData->size() * sizeof(T), vertexData->data(), DRAW_TYPE);
		}

		VBO(const GLenum& DRAW_TYPE, const GLuint& allocationSize_bytes);

		void destroy() override;

		template<typename T>
		void updateData(std::vector<T>* data, const GLuint& offset_bytes = 0) {
			glBufferSubData(GL_ARRAY_BUFFER, offset_bytes, data->size() * sizeof(T), data->data());
		}
	};
}