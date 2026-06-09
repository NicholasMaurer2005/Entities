#pragma once

#include <glew/glew.h>



class VertexArray
{
private:

	//	Private Members

	GLuint m_handle{};



public:

	//	Public Methods

	//static
	static VertexArray create() noexcept;


	//constructor
	VertexArray() noexcept = default;

	~VertexArray() noexcept;

	VertexArray(const VertexArray&) = delete;

	VertexArray(VertexArray&& other) noexcept;

	VertexArray& operator=(const VertexArray&) = delete;

	VertexArray& operator=(VertexArray&& other) noexcept;



	//buffer
	void bind() const noexcept;
};