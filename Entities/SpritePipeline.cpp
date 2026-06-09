#include "SpritePipeline.h"

#include <glm/glm.hpp>
#include <span>
#include <cstdint>
#include <glew/glew.h>

#include "Shader.h"


//	Static Helpers

static SpritePipeline::IndexBufferData generateIndexBufferData(std::size_t size)
{
	SpritePipeline::IndexBufferData data;

	for (std::uint32_t i{}; i < size; ++i)
	{
		const std::uint32_t offset{ i * 4 };

		data.push_back(offset + 0);
		data.push_back(offset + 1);
		data.push_back(offset + 2);

		data.push_back(offset + 0);
		data.push_back(offset + 2);
		data.push_back(offset + 3);
	}
}



//	Public Methods

//draw
void SpritePipeline::draw() const noexcept
{
	m_vertexArray.bind();
	m_spriteSheet.bind();
	m_shader.use();

	glDrawElements(GL_TRIANGLES, m_indexBuffer.vertexCount<std::uint32_t>(), GL_UNSIGNED_INT, nullptr);
}



//setters
void SpritePipeline::buffer(std::span<const DrawData> data) noexcept
{
	if (m_buffer.bufferDynamic(data))
	{
		m_indexBufferData = generateIndexBufferData(data.size());
		m_indexBuffer.buffer<std::uint32_t>(m_indexBufferData);
	}
	else
	{
		m_indexBuffer.bufferSub<std::uint32_t>(std::span(m_indexBufferData.begin(), data.size() * 6));
	}
}

void SpritePipeline::setProjection(const glm::mat4& projection) const noexcept
{
	m_shader.use();

	Shader::uniform(m_projection, projection);
}