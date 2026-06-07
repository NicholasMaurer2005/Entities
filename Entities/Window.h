#pragma once

#include <glew/glew.h>
#include <glfw/glfw3.h>
#include <chrono>



class Window
{
private:

	//	Private Definitions
	
	using Clock = std::chrono::high_resolution_clock;



private:

	//	Private Memebers

	//window
	GLFWwindow* m_window{};
	int m_width{};
	int m_height{};

	//delta time
	Clock::time_point m_lastTime{ Clock::now() };

	//fps title
	float m_frameTime{};
	float m_frameCount{};



private:

	//	Private Methods

	void initializeGLFW();

	float getDeltaTime() noexcept;

	void title(float deltaTime) noexcept;

	void draw() noexcept;



public:

	//	Public Methods

	//constructors
	Window(int width, int height);

	Window(const Window&) = delete;

	Window(Window&& other) noexcept;

	Window& operator=(const Window&) = delete;

	Window& operator=(Window&& other) noexcept;



	//window
	float update();



	//getters
	bool open() const noexcept;



	//setters
	void resize(int width, int height) noexcept;
};