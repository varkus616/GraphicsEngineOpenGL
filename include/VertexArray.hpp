#ifndef VERTEX_ARRAY_HPP
#define VERTEX_ARRAY_HPP

#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"

class VertexArray 
{

public:
	VertexArray();
	~VertexArray();

	VertexArray(const VertexArray& other);
	VertexArray& operator=(const VertexArray& other);

	VertexArray(VertexArray&& other) noexcept;
	VertexArray& operator=(VertexArray&& other) noexcept;

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
	void Reset() { _currentAttribIndex = 0; } ;

	void Bind() const;
	void Unbind() const;

private:
	GLuint _rendererID;
	GLuint _currentAttribIndex;

};

#endif // !VERTEX_ARRAY_HPP
