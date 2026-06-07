#include "Application.h"



Application::Application()
{
	while (m_window.open())
	{
		m_window.update();
	}
}