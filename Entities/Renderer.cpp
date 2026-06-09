#include "Renderer.h"

#include <span>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>



//	Public Methods

void Renderer::draw() const noexcept
{

}

void Renderer::submit(std::span<const SpriteDrawData> sprites) noexcept
{
	m_spritePipeline.buffer(sprites);
}

void Renderer::resize(float width, float height) const noexcept
{
	static constexpr float viewportHeight{ 2.0f };

	const float aspectRatio{ static_cast<float>(width) / height };
	const float viewportWidth{ viewportHeight * aspectRatio };

	const glm::mat4 projection{ glm::ortho(-viewportWidth * 0.5f, viewportWidth * 0.5f, -viewportHeight * 0.5f, viewportHeight * 0.5f) };

	m_spritePipeline.setProjection(projection);
}