#include "PlayerPipeline.h"

#include <array>
#include <cstddef>
#include <glm/glm.hpp>
#include <utility>

#include "Buffer.h"
#include "Image.h"
#include "Shader.h"
#include "Texture.h"
#include "VertexArray.h"


//	Static Helpers

struct Vertex
{
	glm::vec2 position, texCoord;
};

static consteval std::pair<std::array<Vertex, 4>, std::array<int, 6>> quadBuffers(float width, int spriteCount)
{
	const float offset{ width * 0.5f };

	const float textureHeight{ 1.0f };
	const float textureWidth{ textureHeight / spriteCount };

	const std::array<Vertex, 4> vertexData{
		Vertex(glm::vec2(-offset, -offset), glm::vec2(0.0f, 0.0f)),
		Vertex(glm::vec2(offset, -offset), glm::vec2(textureWidth, 0.0f)),
		Vertex(glm::vec2(offset, offset), glm::vec2(textureWidth, textureHeight)),
		Vertex(glm::vec2(-offset, offset), glm::vec2(0.0f, textureHeight)),
	};

	const std::array<int, 6> indexData{
		0, 1, 2,
		0, 2, 3
	};

	return std::pair(vertexData, indexData);
}



//	Public Methods

//constructors
PlayerPipeline::PlayerPipeline(const glm::mat4& projection) : 
	m_vertexArray{ VertexArray::create() },
	m_buffer{ Buffer::Target::ArrayBuffer, Buffer::Usage::StaticDraw },
	m_indexBuffer{ Buffer::Target::IndexBuffer, Buffer::Usage::StaticDraw },
	m_shader{ "assets/playerVertex.glsl", "assets/defaultFragment.glsl" },
	m_spriteSheet{ Image("assets/wizard-sprite.png"), Texture::Filter::Linear, Texture::Filter::Linear },
	m_projection{ m_shader.uniformLocation("projection") },
	m_spriteFrame{ m_shader.uniformLocation("spriteFrame") }
{
	m_shader.use();

	Shader::uniform(m_projection, projection);
	Shader::uniform(m_spriteFrame, 1);

	static constexpr int textureWidthPixels{ 32 };
	static constexpr int textureHeightPixels{ 32 };
	static constexpr float spriteWidth{ 2.0f / 10.0f }; // 1/10th of the screen width

	auto [vertexData, indexData] = quadBuffers(spriteWidth, 2);

	m_vertexArray.bind();
	
	m_buffer.bind();
	m_buffer.buffer<Vertex>(vertexData);
	
	m_indexBuffer.bind();
	m_indexBuffer.buffer<int>(indexData);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(0));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, texCoord)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
}



//pipeline
void PlayerPipeline::bind() const noexcept
{
	m_vertexArray.bind();
	m_spriteSheet.bind();
	m_shader.use();
}

void PlayerPipeline::update(const UpdateEvent& event) const noexcept
{
	if (event.projection) Shader::uniform(m_projection, *event.projection);

	Shader::uniform(m_spriteFrame, event.spriteFrame);
}

void PlayerPipeline::draw() const noexcept
{
	glDrawElements(GL_TRIANGLES, m_indexBuffer.vertexCount<int>(), GL_UNSIGNED_BYTE, nullptr);
}