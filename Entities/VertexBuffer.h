#pragma once

#include <glew/glew.h>



class VertexBuffer
{
private:

	//	Private Members

	GLuint m_handle{};



public:

	//	Public Methods

	//static
	static VertexBuffer create() noexcept;


	//constructor
	VertexBuffer() noexcept = default;

	~VertexBuffer() noexcept;

	VertexBuffer(const VertexBuffer&) = delete;

	VertexBuffer(VertexBuffer&& other) noexcept;

	VertexBuffer& operator=(const VertexBuffer&) = delete;

	VertexBuffer& operator=(VertexBuffer&& other) noexcept;



	//buffer
	void bind() const noexcept;
};