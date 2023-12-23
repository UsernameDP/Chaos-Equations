#pragma once 

namespace GLCore::Extension::Primitives {
	class GLBindableAtInterface {
	public:
		virtual void bindAt(const GLuint& loc) = 0;
	};

}