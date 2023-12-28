#pragma once
#include "GLBufferObject.hpp"
#include "GLBindableAtInterface.hpp"


namespace GLCore::Extension::Primitives {

	class SSBO : public GLBufferObject, public GLBindableAtInterface {

	public:
		template<typename T>
		SSBO(const GLenum& DRAW_TYPE, std::vector<T>* data) : GLBufferObject(GL_SHADER_STORAGE_BUFFER) {
			glGenBuffers(1, &ID);
			bind();
			glBufferData(GL_SHADER_STORAGE_BUFFER, data->size() * sizeof(T), data->data(), DRAW_TYPE); //once data is allocated on GPU, it is stored there
			unbind();
		}

		SSBO(const GLenum& DRAW_TYPE, const GLuint& allocationSize_bytes);


		void bindAt(const GLuint& loc) override;
		void unbind() override;
		void destroy() override;

		template<typename T>
		void updateData(std::vector<T>* data) {
			bind();
			glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, data->size() * sizeof(T), data->data());
			unbind();
		}
		template<typename T>
		void updateAndReallocateData(const GLenum& DRAW_TYPE, std::vector<T>* data) {
			bind();
			glBufferData(GL_SHADER_STORAGE_BUFFER, data->size() * sizeof(T), data->data(), DRAW_TYPE);
			unbind();
		}
		void reallocateData(const GLenum& DRAW_TYPE, const GLuint& allocationSize_bytes);

		template<typename T>
		void readDataTo(std::vector<T>* dest) {
			bind();
			void* src = glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_READ_ONLY); //a pointer to the SSBO data stored on GPU
			if (src) {
				memcpy(dest->data(), src, dest->size() * sizeof(T));
			}
			glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
			unbind();
		}
	};

}