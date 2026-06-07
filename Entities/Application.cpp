#include "Application.h"

#include <glew/glew.h>
#include <glm/glm.hpp>
#include <array>

#include "VertexBuffer.h"
#include "Buffer.h"
#include "Texture.h"
#include "Shader.h"
#include "Image.h"
#include <cstddef>



Application::Application()
{
	VertexBuffer vertexBuffer{ VertexBuffer::create() };

	Buffer buffer{ Buffer::Target::ArrayBuffer, Buffer::Usage::StaticDraw };

	Texture texture{ Image("assets/castle.png"), Texture::Filter::Linear, Texture::Filter::Linear };

	Shader shader{ "assets/defaultVertex.glsl", "assets/defaultFragment.glsl" };

	vertexBuffer.bind();
	buffer.bind();
	texture.bind();
	shader.use();

	struct Vertex
	{
		glm::vec2 position, texCoord;
	};

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(0));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, texCoord)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	static constexpr std::array<Vertex, 3> triangle{
		Vertex(glm::vec2(-0.5f, -0.5f), glm::vec2(0.0f, 0.0f)),
		Vertex(glm::vec2(0.5f, -0.5f), glm::vec2(1.0f, 0.0f)),
		Vertex(glm::vec2(0.0f, 0.5f), glm::vec2(0.5f, 1.0f))
	};

	buffer.buffer<Vertex>(triangle);

	while (m_window.open())
	{
		m_window.clear();

		glDrawArrays(GL_TRIANGLES, 0, buffer.vertexCount<Vertex>());

		m_window.update();
	}
}