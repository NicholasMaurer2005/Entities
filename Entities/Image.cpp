#include "Image.h"

#include <cstdint>
#include <string_view>
#include <stdexcept>
#include <format>
#include <utility>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>



//	Public Methods

//constructors
Image::Image(std::string_view source, bool flipped)
{
	stbi_set_flip_vertically_on_load(flipped);

	m_data = stbi_load(source.data(), &m_width, &m_height, &m_channels, 0);

	if (!m_data) throw std::runtime_error(std::format("Unable to find image source {}", source));
}

Image::~Image() noexcept
{
	stbi_image_free(m_data);
}

Image::Image(Image&& other) noexcept :
	m_data{ std::exchange(other.m_data, nullptr) },
	m_width{ other.m_width },
	m_height{ other.m_height },
	m_channels{ other.m_channels } {}

Image& Image::operator=(Image&& other) noexcept
{
	m_data = std::exchange(other.m_data, nullptr);
	m_width = other.m_width;
	m_height = other.m_height;
	m_channels = other.m_channels;

	return *this;
}



//getters
int Image::width() const noexcept
{
	return m_width;
}

int Image::height() const noexcept
{
	return m_height;
}

int Image::channels() const noexcept
{
	return m_channels;
}

const std::uint8_t* Image::data() const noexcept
{
	return m_data;
}