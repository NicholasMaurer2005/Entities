#include "Buffer.h"

#include <glew/glew.h>
#include <utility>



//	Public Methods

//constructor
Buffer::Buffer(Target target, Usage usage) noexcept :
	m_target{ static_cast<GLenum>(target) },
	m_usage{ static_cast<GLenum>(usage) }
{
	glGenBuffers(1, &m_handle);
}

Buffer::~Buffer() noexcept
{
	glDeleteBuffers(1, &m_handle);
}

Buffer::Buffer(Buffer&& other) noexcept :
	m_handle{ std::exchange(other.m_handle, 0) },
	m_target{ other.m_target },
	m_usage{ other.m_usage },
	m_size{ other.m_size } {}

Buffer& Buffer::operator=(Buffer&& other) noexcept
{
	glDeleteBuffers(1, &m_handle);

	m_handle = std::exchange(other.m_handle, 0);
	m_target = other.m_target;
	m_usage = other.m_usage;
	m_size = other.m_size;

	return *this;
}



//buffer
void Buffer::bind() const noexcept
{
	glBindBuffer(m_target, m_handle);
}