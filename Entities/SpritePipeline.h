#pragma once

#include <vector>
#include <cstdint>

#include "Texture.h"
#include "Buffer.h"
#include "Shader.h"
#include "Image.h"
#include "Vertex.h"
#include "VertexArray.h"



class SpritePipeline
{
public:

	//	Public Definitions

	struct DrawData
	{
		Vertex a, b, c, d;
	};

	using IndexBufferData = std::vector<std::uint32_t>;



private:

	//	Private Members

	Texture m_spriteSheet{ Image("assets/sprite-sheet.png"), Texture::Filter::Nearest, Texture::Filter::Linear };
	VertexArray m_vertexArray{ VertexArray::create() };
	Buffer m_indexBuffer{ Buffer::Target::IndexBuffer, Buffer::Usage::StaticDraw };
	Buffer m_buffer{ Buffer::Target::ArrayBuffer, Buffer::Usage::StaticDraw };

	Shader m_shader{ "assets/spriteVertex.glsl", "assets/spriteFragment.glsl" };
	Shader::Uniform m_projection{ m_shader.uniformLocation("projection") };

	IndexBufferData m_indexBufferData;



public:

	//	Public Methods


	//draw

	void draw() const noexcept;



	//setters
	void buffer(std::span<const DrawData> data) noexcept;

	void setProjection(const glm::mat4& projection) const noexcept;
};

