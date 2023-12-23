#pragma once
#include "GLBindableInterface.hpp"

namespace GLCore::Extension::Primitives {

	class GLBufferObject : public GLBindableInterface {
	protected:
		GLenum type;
	public:
		GLBufferObject(const GLenum& type);
		virtual ~GLBufferObject();

		virtual void bind() override;
		virtual void unbind() override;
	};

}