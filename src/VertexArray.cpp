#include "VertexArray.hpp"
#include "Utilities.hpp"

VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &_rendererID));
	this->Bind();
}
VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &_rendererID));
	_rendererID = 0;

}

VertexArray::VertexArray(const VertexArray& other) :
	_rendererID(other._rendererID)
{
	
}

VertexArray& VertexArray::operator=(const VertexArray& other)
{
	_rendererID = other._rendererID;
	return *this;
}

VertexArray::VertexArray(VertexArray&& other) noexcept
	: _rendererID(other._rendererID)
{ 
	other._rendererID = 0;
}

VertexArray& VertexArray::operator=(VertexArray&& other) noexcept
{
	if (this != &other)
	{
		glDeleteVertexArrays(1, &_rendererID);
		_rendererID = other._rendererID;
		other._rendererID = 0;
	}
	return *this;
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	Bind();  
	vb.Bind();  

	const auto& elements = layout.GetElements();
	uintptr_t offset = 0;  

	for (GLuint i = 0; i < elements.size(); i++)
	{
		//printf("ID: %d | I:%d | Index:%d\n",this->_rendererID, i, _currentAttribIndex);
		const auto& element = elements[i];
		GLCall(glEnableVertexAttribArray(i));

		GLCall(glVertexAttribPointer(i, element.count, element.type,
			element.normalized, layout.GetStride(),
			reinterpret_cast<const void*>(offset)));

		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
		_currentAttribIndex++;
	}
}

void VertexArray::Bind() const
{
	GLCall(glBindVertexArray(_rendererID));
}

void VertexArray::Unbind() const
{
	GLCall(glBindVertexArray(0));
}