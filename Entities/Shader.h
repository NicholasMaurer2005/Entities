#pragma once

#include <glew/glew.h>
#include <string_view>
#include <glm/glm.hpp>



class Shader
{
private:

	//	Private Members

	GLuint m_handle{};



public:

	//	Public Methods

	//static
	static void uniform(GLuint location, glm::vec2 value) noexcept;



	//constructors
	Shader() noexcept = default;

	~Shader() noexcept;

	Shader(std::string_view vertexSource, std::string_view fragmentSource);

	Shader(const Shader&) = delete;

	Shader(Shader&& other) noexcept;

	Shader& operator=(const Shader&) = delete;

	Shader& operator=(Shader&& other) noexcept;



	//setters
	void bind() const noexcept;

	GLint uniformLocation(std::string_view name) const;

};

