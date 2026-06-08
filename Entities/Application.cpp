#include "Application.h"

#include <glew/glew.h>
#include <glm/glm.hpp>
#include <array>
#include <cstddef>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#include "VertexBuffer.h"
#include "Buffer.h"
#include "Texture.h"
#include "Shader.h"
#include "Image.h"



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
		Vertex(glm::vec2(-1.0f, -1.0f), glm::vec2(0.0f, 0.0f)),
		Vertex(glm::vec2(1.0f, -1.0f), glm::vec2(1.0f, 0.0f)),
		Vertex(glm::vec2(0.0f, 1.0f), glm::vec2(0.5f, 1.0f))
	};

	buffer.buffer<Vertex>(triangle);

	const GLint projectionLocation{ shader.uniformLocation("project") };
	const GLint transformLocation{ shader.uniformLocation("transform") };

	Shader::uniform(projectionLocation, glm::ortho(-1, 1, -1, 1));

	static constexpr std::array<Vertex, 6> quad{
		Vertex(glm::vec2(-0.1f, -0.1f), glm::vec2(0.0f, 0.0f)),
		Vertex(glm::vec2(0.1f, -0.1f), glm::vec2(1.0f, 0.0f)),
		Vertex(glm::vec2(0.1f, 0.1f), glm::vec2(1.0f, 1.0f)),
		Vertex(glm::vec2(-0.1f, -0.1f), glm::vec2(0.0f, 0.0f)),
		Vertex(glm::vec2(0.1f, 0.1f), glm::vec2(1.0f, 1.0f)),
		Vertex(glm::vec2(-0.1f, 0.1f), glm::vec2(0.0f, 1.0f))
	};

	Texture wizardTexture{ Image("assets/wizard-sprite.png"), Texture::Filter::Nearest, Texture::Filter::Nearest };
	Shader wizardShader{ "assets/playerVertex.glsl", "assets/defaultFragment.glsl" };
	VertexBuffer wizardVertexBuffer;
	Buffer wizardBuffer{ Buffer::Target::ArrayBuffer, Buffer::Usage::StaticDraw };
	wizardShader.use();
	const GLint wizardTransformLocation{ wizardShader.uniformLocation("transform") };

	Shader::uniform(wizardTransformLocation, glm::ortho(-1, 1, -1, 1));

	wizardVertexBuffer.bind();
	wizardBuffer.bind();
	wizardBuffer.buffer<Vertex>(quad);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(0));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, texCoord)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	while (m_window.open())
	{
		//clear screen
		m_window.clear();

		//background
		texture.bind();
		shader.use();
		vertexBuffer.bind();

		//if (m_window.newProjection()) Shader::uniform(projectionLocation, m_window.projection());
		if (m_gameState.newTransform()) Shader::uniform(transformLocation, m_gameState.transform());

		

		glDrawArrays(GL_TRIANGLES, 0, buffer.vertexCount<Vertex>());

		//wizard
		wizardTexture.bind();
		wizardShader.use();
		wizardVertexBuffer.bind();

		glDrawArrays(GL_TRIANGLES, 0, wizardBuffer.vertexCount<Vertex>());

		//update scene and draw window
		m_gameState.update(m_window.input(), m_window.update());
	}
}