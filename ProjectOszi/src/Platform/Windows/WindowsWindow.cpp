#include <ozpch.h>
#include "WindowsWindow.h"

namespace Oszi {
	static bool s_GLFWinitialized = false;

	Window* Window::Create(const WindowProps& props) 
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Hight = props.Hight;
		m_Data.Width = props.Width;

		OZ_INFO("Creating Window Name:{0} Size:{1}x{2}", props.Title, props.Width, props.Hight);

		if (!s_GLFWinitialized)
		{
			int success = glfwInit();
			OZ_ASSERT(success, "Could not initialize GLFW!");
			s_GLFWinitialized = true;
		}

		m_Window = glfwCreateWindow((int)props.Width, (int)props.Hight, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}
}