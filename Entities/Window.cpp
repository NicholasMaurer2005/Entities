#include "Window.h"

#include <glew/glew.h>
#include <glfw/glfw3.h>
#include <stdexcept>
#include <utility>
#include <chrono>
#include <format>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Input.h"



//	Static Helpers

static void windowSizeCallback(GLFWwindow* window, int width, int height) noexcept
{
	Window& user{ *reinterpret_cast<Window*>(glfwGetWindowUserPointer(window)) };

	user.resize(width, height);
}



//	Private Methods

void Window::initializeGLFW()
{
	if (!glfwInit()) throw std::runtime_error("Unable to initialize GLFW.");

	m_window = glfwCreateWindow(m_width, m_height, "initializing", nullptr, nullptr);

	if (!m_window) throw std::runtime_error("Unable to create a window.");

	glfwMakeContextCurrent(m_window);

	if (glewInit() != GLEW_OK) throw std::runtime_error("Unable to initialize GLEW.");

	glfwSetWindowUserPointer(m_window, this);
	glfwSetWindowSizeCallback(m_window, windowSizeCallback);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

float Window::getDeltaTime() noexcept
{
	const Clock::time_point now{ Clock::now() };

	const float elapsed{ std::chrono::duration<float>(now - m_lastTime).count() };

	m_lastTime = now;

	return elapsed;
}

void Window::title(float deltaTime) noexcept
{
	m_frameTime += deltaTime;
	++m_frameCount;

	if (m_frameTime > 1.0f)
	{
		const float fps{ m_frameCount / m_frameTime };

		glfwSetWindowTitle(m_window, std::format("Entities = {:.3f}fps", fps).data());

		m_frameTime = 0.0f;
		m_frameCount = 0;
	}
}



//	Public Methods

//constructors
Window::Window(int width, int height)
{
	resize(width, height);
	initializeGLFW();
}

Window::~Window() noexcept
{
	glfwDestroyWindow(m_window);

	glfwTerminate();
}

Window::Window(Window&& other) noexcept : 
	m_window{ std::exchange(other.m_window, nullptr) },
	m_width{ other.m_width},
	m_height{ other.m_height } {}

Window& Window::operator=(Window&& other) noexcept
{
	m_window = std::exchange(other.m_window, nullptr);
	m_width = other.m_width;
	m_height = other.m_height;

	return *this;
}



//window
void Window::clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

float Window::update()
{
	const float deltaTime{ getDeltaTime() };

	title(deltaTime);

	glfwSwapBuffers(m_window);
	glfwPollEvents();

	return deltaTime;
}



//getters
bool Window::open() const noexcept
{
	return !glfwWindowShouldClose(m_window);
}

Input Window::input() const noexcept
{
	return Input(m_window);
}

int Window::width() const noexcept
{
	return m_width;
}

int Window::height() const noexcept
{
	return m_height;
}

bool Window::newSize() noexcept
{
	return std::exchange(m_newSize, false);
}



//setters
void Window::resize(int width, int height) noexcept
{
	m_width = width;
	m_height = height;

	glViewport(0, 0, width, height);
}