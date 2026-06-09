#include "Vertex.h"

#include <glew/glew.h>
#include <cstddef>



void Vertex::initializeAttribPointers() noexcept
{
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, position)));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, texCoord)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
}