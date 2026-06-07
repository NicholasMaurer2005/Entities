#pragma once

#include <glew/glew.h>

#include "Image.h"



class Texture
{
public:

	//	Public Definitions

	enum class Filter : GLint
	{
		Nearest = GL_NEAREST,
		Linear = GL_LINEAR
	};


private:

	//	Private Members

	GLuint m_handle{};



public:

	//	Public Methods

	//constructors
	Texture() noexcept = default;

	~Texture() noexcept;

	Texture(Image image, Filter minFilter, Filter magFilter);

	Texture(const Texture&) = delete;

	Texture(Texture&& other) noexcept;

	Texture& operator=(const Texture&) = delete;

	Texture& operator=(Texture&& other) noexcept;
	


	//setters
	void bind() const noexcept;
};


