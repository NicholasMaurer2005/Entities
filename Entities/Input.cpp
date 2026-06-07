#include "Input.h"

#include <glew/glew.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>



bool Input::keyDown(Key key) const noexcept
{
	return glfwGetKey(m_window, static_cast<int>(key));
}

glm::vec2 Input::cursorPosition() const noexcept
{
	glm::dvec2 position{};

	glfwGetCursorPos(m_window, &position.x, &position.y);

	return glm::vec2(position);
}