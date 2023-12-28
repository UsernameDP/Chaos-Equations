#pragma once
#include "GLBufferObject.hpp"

namespace GLCore::Extension::Primitives {
	class EBO : public GLBufferObject {
	public:
		EBO(const GLenum& DRAW_TYPE, std::vector<unsigned int>* indices);

		void destroy() override;
	public:

		void updateData(std::vector<unsigned int>* data, const GLuint& offset_bytes = 0);

		void updateAndReallocateData(const GLenum& DRAW_TYPE, std::vector<unsigned int>* data);
	};
}