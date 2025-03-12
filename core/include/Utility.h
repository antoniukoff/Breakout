#include <gl/glew.h>

namespace gl_utils
{
	inline unsigned int gl_type_to_cpp_size(int gl_type)
	{
		switch (gl_type)
		{
		case GL_SHORT:          return sizeof(short);
		case GL_UNSIGNED_SHORT: return sizeof(unsigned short);
		case GL_INT:            return sizeof(int);
		case GL_UNSIGNED_INT:   return sizeof(unsigned int);
		case GL_FLOAT:          return sizeof(float);
		case GL_DOUBLE:         return sizeof(double);

		case GL_2_BYTES:        return 2;
		case GL_3_BYTES:        return 3;
		case GL_4_BYTES:        return 4;

		default:
			return 0;
		}
	}

	inline unsigned int get_texture_type(int gl_type)
	{
		switch (gl_type)
		{
		case GL_TEXTURE_2D:          return 0;
		case GL_TEXTURE_3D:			 return 1;
		case GL_TEXTURE_CUBE_MAP:    return 2;

		default:
			return -1;
		}
	}
}

#define EMPTY_TEXTURE_ID -1
