#include <exception>
#include <format>
#include <iostream>

#include "Application.h"



int main()
{
	try
	{
		Application app;
	}
	catch (std::exception& exception)
	{
		std::cout << std::format("failed due to: {}", exception.what());
	}
}