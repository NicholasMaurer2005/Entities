#include "Application.h"

#include <glew/glew.h>
#include <glm/glm.hpp>
#include <array>
#include <cstddef>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#include "Window.h"
#include "PlayerPipeline.h"



Application::Application()
{
	PlayerPipeline playerPipeline{ m_window.projection() };

	while (m_window.open())
	{
		m_window.clear();

		PlayerPipeline::UpdateEvent event{ m_window.newProjection() ? &m_window.projection() : nullptr, m_gameState.playerSpriteFrame() };

		playerPipeline.bind();
		playerPipeline.update(event);
		playerPipeline.draw();

		m_gameState.update(m_window.input(), m_window.update());
	}
}