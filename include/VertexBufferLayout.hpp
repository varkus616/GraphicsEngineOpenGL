#ifndef VERTEX_BUFFER_LAYOUT_HPP
#define VERTEX_BUFFER_LAYOUT_HPP

#include <vector>
#include <GL/glew.h>
#include "Utilities.hpp"

struct VertexBufferElement
{
	GLuint type;
	GLuint count;
	GLboolean normalized;
	static int GetSizeOfType(GLuint type)
	{
		switch (type)
		{
		case GL_FLOAT: return sizeof(GLfloat);
		case GL_UNSIGNED_INT: return sizeof(GLuint);
		case GL_BYTE: return sizeof(GLbyte);
		case GL_UNSIGNED_BYTE: return sizeof(GLubyte);
		}
		//ASSERT(false);
		return 0;
	}
};


class VertexBufferLayout
{
private:
	std::vector<VertexBufferElement> _Elements;
	GLuint _Stride;
public:
	VertexBufferLayout(): _Stride(0){}


	template<typename T>
	void Push(GLuint count) {
		static_assert(sizeof(T) == 0, "Type not supported.");
	}

	template<>
	void Push<GLfloat>(GLuint count) {
		_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
		_Stride += VertexBufferElement::GetSizeOfType(GL_FLOAT) * count;
	}

	template<>
	void Push<GLuint>(GLuint count) {
		_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT) * count;
	}

	template<>
	void Push<GLubyte>(GLuint count) {
		_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE) * count;
	}
	template<>
	void Push<GLbyte>(GLuint count) {
		_Elements.push_back({ GL_BYTE, count, GL_TRUE });
		_Stride += VertexBufferElement::GetSizeOfType(GL_BYTE) * count;
	}

	inline const std::vector<VertexBufferElement> GetElements()const { return _Elements; }
	inline GLuint GetStride() const { return _Stride; }
};


#endif // !VERTEX_BUFFER_LAYOUT_HPP

