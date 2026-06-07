#include "Texture.h"

#include "Image.h"



//constructors
Texture::~Texture() noexcept
{
	glDeleteTextures(1, &m_handle);
}

Texture::Texture(Image image, int minFilter, int magFilter)
{
	glGenTextures(1, &m_handle);

	bind();

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	const GLint format{ image.channels() == 4 ? GL_RGBA : GL_RGB };

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width(), image.height(), 0, format, GL_UNSIGNED_BYTE, image.data());
}

Texture::Texture(Texture&& other) noexcept : 
	m_handle{ std::exchange(other.m_handle, 0) } {}

Texture& Texture::operator=(Texture&& other) noexcept
{
	m_handle = std::exchange(other.m_handle, 0);

	return *this;
}



//setters
void Texture::bind() const noexcept
{
	glBindTexture(GL_TEXTURE_2D, m_handle);
}