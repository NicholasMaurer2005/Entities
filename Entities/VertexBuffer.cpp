#include "VertexBuffer.h"

#include <glew/glew.h>
#include <utility>



//	Public Methods

//static
VertexBuffer VertexBuffer::create() noexcept
{
	VertexBuffer buffer;

	glGenVertexArrays(1, &buffer.m_handle);

	return buffer;
}



//constructor
VertexBuffer::~VertexBuffer() noexcept
{
	glDeleteVertexArrays(1, &m_handle);
}

VertexBuffer::VertexBuffer(VertexBuffer&& other) noexcept :
	m_handle{ std::exchange(other.m_handle, 0) } {}

VertexBuffer& VertexBuffer::operator=(VertexBuffer&& other) noexcept
{
	glDeleteVertexArrays(1, &m_handle);

	m_handle = std::exchange(other.m_handle, 0);

	return *this;
}



//buffer
void VertexBuffer::bind() const noexcept
{
	glBindVertexArray(m_handle);
}