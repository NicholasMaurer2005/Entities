#pragma once

#include <glm/glm.hpp>



struct Vertex
{
	glm::vec3 position, texCoord;

	static void initializeAttribPointers() noexcept;
};
