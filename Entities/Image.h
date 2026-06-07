#pragma once

#include <cstdint>
#include <string_view>



class Image
{
private:

	//	Private Members

	std::uint8_t* m_data;
	int m_width;
	int m_height;
	int m_channels;



public:

	//	Public Methods

	//constructors
	Image(std::string_view source);

	~Image() noexcept;

	Image(const Image&) = delete;

	Image(Image&& other) noexcept;

	Image& operator=(const Image&) = delete;

	Image& operator=(Image&& other) noexcept;



	//getters
	int width() const noexcept;

	int height() const noexcept;

	int channels() const noexcept;

	const std::uint8_t* data() const noexcept;
};

