#include "Shader.h"

#include <format>
#include <fstream>
#include <glew/glew.h>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>
#include <glm/gtc/type_ptr.hpp>



//	Static Helpers

struct ShaderDeleter
{
	GLuint handle;

	ShaderDeleter(GLuint handle) noexcept
		: handle{ handle } {}

	~ShaderDeleter() noexcept
	{
		glDeleteShader(handle);
	}

	ShaderDeleter(const ShaderDeleter&) = delete;

	ShaderDeleter(ShaderDeleter&& other) noexcept
		: handle{ std::exchange(other.handle, 0) } {}

	ShaderDeleter& operator=(const ShaderDeleter&) = delete;

	ShaderDeleter& operator=(ShaderDeleter&& other) noexcept
	{
		handle = std::exchange(other.handle, 0);
	}
};

static std::string readFile(std::string_view source)
{
	std::ifstream in{ source.data(), std::ios::binary | std::ios::ate };

	if (!in) throw std::runtime_error(std::format("Unable to open the file {}.", source));

	const std::streampos size{ in.tellg() };

	in.seekg(0);

	std::string data;
	data.resize(size);
	in.read(data.data(), size);

	return data;
}

static ShaderDeleter compileShader(std::string_view source, GLenum shaderType)
{
	ShaderDeleter shader{ glCreateShader(shaderType) };

	const std::string data{ readFile(source) };
	const char* dataPtr{ data.data() };

	glShaderSource(shader.handle, 1, &dataPtr, nullptr);

	glCompileShader(shader.handle);

	GLint result{};
	glGetShaderiv(shader.handle, GL_COMPILE_STATUS, &result);

	if (result == GL_FALSE) throw std::runtime_error(std::format("Unable to compile shader from source {}.", source));

	return shader;
}




//	Public Methods

//static
void Shader::uniform(GLuint location, glm::vec2 value) noexcept
{
	glUniform2f(location, value.x, value.y);
}

void Shader::uniform(GLuint location, const glm::mat4& value) noexcept
{
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}


//constructors
Shader::~Shader() noexcept
{
	glDeleteShader(m_handle);
}

Shader::Shader(std::string_view vertexSource, std::string_view fragmentSource)
{
	const ShaderDeleter vertexShader{ compileShader(vertexSource, GL_VERTEX_SHADER) };;
	const ShaderDeleter fragmentShader{ compileShader(fragmentSource, GL_FRAGMENT_SHADER) };

	m_handle = glCreateProgram();

	glAttachShader(m_handle, vertexShader.handle);
	glAttachShader(m_handle, fragmentShader.handle);

	glLinkProgram(m_handle);

	GLint result{};
	glGetProgramiv(m_handle, GL_LINK_STATUS, &result);

	if (result == GL_FALSE) throw std::runtime_error(std::format("Unable to link program with vertex source {} and fragment source {}", vertexSource, fragmentSource));
}

Shader::Shader(Shader&& other) noexcept : 
	m_handle{ std::exchange(other.m_handle, 0) } {}

Shader& Shader::operator=(Shader&& other) noexcept
{
	glDeleteProgram(m_handle);

	m_handle = std::exchange(other.m_handle, 0);

	return *this;
}



//setters
void Shader::use() const noexcept
{
	glUseProgram(m_handle);
}

GLint Shader::uniformLocation(std::string_view name) const
{
	const GLint location{ glGetUniformLocation(m_handle, name.data()) };

	if (location < 0) throw std::runtime_error(std::format("Unable to find uniform {}.", name));

	return location;
}