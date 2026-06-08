#include "GameState.h"

#include <glm/gtc/matrix_transform.hpp>
#include <utility>

#include "Input.h"


//	Public Methods

//game state
void GameState::update(Input input, float deltaTime) noexcept
{
	static constexpr float movementSpeed{ 0.1f };

	glm::vec2 playerPosition{ m_playerPosition };

	if (input.keyDown(Input::Key::W)) playerPosition.y += deltaTime * movementSpeed;

	if (input.keyDown(Input::Key::A)) playerPosition.x -= deltaTime * movementSpeed;

	if (input.keyDown(Input::Key::S)) playerPosition.y -= deltaTime * movementSpeed;

	if (input.keyDown(Input::Key::D)) playerPosition.x += deltaTime * movementSpeed;

	if (playerPosition != m_playerPosition)
	{
		m_playerPosition = playerPosition;
		m_transform = glm::translate(glm::mat4(1.0f), glm::vec3(-m_playerPosition, 0.0f));
		m_newTransform = true;
	}
}



//getters
bool GameState::newTransform() noexcept
{
	return std::exchange(m_newTransform, false);
}

const glm::mat4& GameState::transform() const noexcept
{
	return m_transform;
}