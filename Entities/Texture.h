#pragma once

#include <glew/glew.h>
#include <glm/glm.hpp>
#include <string_view>

#include "Image.h"



class Texture
{
private:

	//	Private Members

	GLuint m_handle{};



public:

	//	Public Methods

	//constructors
	Texture() noexcept = default;

	~Texture() noexcept;

	Texture(Image image, int minFilter, int magFilter);

	Texture(const Texture&) = delete;

	Texture(Texture&& other) noexcept;

	Texture& operator=(const Texture&) = delete;

	Texture& operator=(Texture&& other) noexcept;
	


	//setters
	void bind() const noexcept;
};


