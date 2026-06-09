#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Input.h"
#include "PlayerPipeline.h"



class GameState
{
private:

	//	Private Members

	glm::vec2 m_playerPosition{};
	bool m_newTransform{ true };
	glm::mat4 m_transform{ glm::translate(glm::mat4(1.0f), glm::vec3(m_playerPosition, 0.0f)) };

	bool m_playerRight{};


public:

	//	Public Methods

	//game state
	void update(Input input, float deltaTime) noexcept;



	//getters
	bool newTransform() noexcept;

	const glm::mat4& transform() const noexcept;

	int playerSpriteFrame() const noexcept;
};

