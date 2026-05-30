#include "pnpch.h"
#include "WindowsWindow.h"
#include "Phanes/Log.h"

namespace Phanes {

	static bool GLFWInitialized__ = false;

	Window* Window::Create(const WindowProps& props) { return new WindowsWindow(props); }

	WindowsWindow::WindowsWindow(const WindowProps& props) { Init(props); }
	WindowsWindow::~WindowsWindow() { Shutdown(); }

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(Window__);
	}

	bool WindowsWindow::IsVSync() const
	{
		return false;
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		if(enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		Data__.VSync = enabled;
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		Data__.Width = props.Width;
		Data__.Height = props.Height;
		Data__.Title = props.Title;

		PN_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		if (!GLFWInitialized__) {
			int success = glfwInit();
			PN_CORE_ASSERT(success, "Could not initialize GLFW!");
			GLFWInitialized__ = true;
		}

		Window__ = glfwCreateWindow((int)props.Width, (int)props.Height, Data__.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(Window__);
		glfwSetWindowUserPointer(Window__, &Data__);
		SetVSync(true);
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(Window__);
	}
};