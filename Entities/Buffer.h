#pragma once

#include <glew/glew.h>
#include <span>



class Buffer
{
public:

	//	Public Definitions

	enum class Target : GLenum
	{
		ArrayBuffer = GL_ARRAY_BUFFER,
		IndexBuffer = GL_ELEMENT_ARRAY_BUFFER
	};

	enum class Usage : GLenum
	{
		StaticDraw = GL_STATIC_DRAW,
		DynamicDraw = GL_DYNAMIC_DRAW,
		StreamDraw = GL_STREAM_DRAW
	};



private:

	//	Private Members

	GLuint m_handle{};
	GLenum m_target{};
	GLenum m_usage{};
	std::size_t m_size{};
	std::size_t m_capacity{};



public:

	//	Public Methods

	//constructor
	Buffer() noexcept = default;

	Buffer(Target target, Usage usage) noexcept;

	~Buffer() noexcept;

	Buffer(const Buffer&) = delete;

	Buffer(Buffer&& other) noexcept;

	Buffer& operator=(const Buffer&) = delete;

	Buffer& operator=(Buffer&& other) noexcept;



	//buffer
	void bind() const noexcept;

	template<typename T>
	void buffer(std::span<const T> data) noexcept
	{
		m_size = data.size_bytes();
		m_capacity = data.size_bytes();

		glBufferData(static_cast<GLenum>(m_target), m_size, data.data(), m_usage);
	}

	template<typename T>
	void bufferSub(std::span<const T> data) noexcept
	{
		m_size = data.size_bytes();

		glBufferSubData(m_target, 0, m_size, data.data());
	}

	template<typename T>
	bool bufferDynamic(std::span<const T> data)
	{
		if (data.size_bytes() > m_capacity)
		{
			buffer<T>(data);

			return true;
		}
		else
		{
			bufferSub<T>(data);

			return false;
		}
	}

	template<typename T>
	GLsizei vertexCount() const noexcept
	{
		return static_cast<GLsizei>(m_size / sizeof(T));
	}
};