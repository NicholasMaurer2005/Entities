#include "VertexArray.h"

#include <glew/glew.h>
#include <utility>



//	Public Methods

//static
VertexArray VertexArray::create() noexcept
{
	VertexArray buffer;

	glGenVertexArrays(1, &buffer.m_handle);

	return buffer;
}



//constructor
VertexArray::~VertexArray() noexcept
{
	glDeleteVertexArrays(1, &m_handle);
}

VertexArray::VertexArray(VertexArray&& other) noexcept :
	m_handle{ std::exchange(other.m_handle, 0) } {}

VertexArray& VertexArray::operator=(VertexArray&& other) noexcept
{
	glDeleteVertexArrays(1, &m_handle);

	m_handle = std::exchange(other.m_handle, 0);

	return *this;
}



//buffer
void VertexArray::bind() const noexcept
{
	glBindVertexArray(m_handle);
}