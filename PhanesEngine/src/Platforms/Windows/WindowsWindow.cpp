#include "pnpch.h"
#include "WindowsWindow.h"

#include "Phanes/Events/AppEvents.h"
#include "Phanes/Events/KeyEvents.h"
#include "Phanes/Events/MouseEvents.h"

#include <glad/glad.h>

namespace Phanes {

	static bool GLFWInitialized__ = false;
	static void GLFWErrorCallback(int error, const char* description) { PN_CORE_LOG_ERROR("GLFW Error ({0}): {1}", error, description); }

	Window* Window::Create(const WindowProps& props) { return new WindowsWindow(props); }

	WindowsWindow::WindowsWindow(const WindowProps& props) { Init(props); }
	WindowsWindow::~WindowsWindow() { Shutdown(); }

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(window_);
	}

	bool WindowsWindow::IsVSync() const
	{
		return false;
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		if(enabled) glfwSwapInterval(1);
		else glfwSwapInterval(0);
		data_.VSync = enabled;
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		data_.Width = props.Width;
		data_.Height = props.Height;
		data_.Title = props.Title;

		PN_CORE_LOG_INFO("Creating window: Title = {0}, ({1}, {2})", props.Title, props.Width, props.Height);

		if (!GLFWInitialized__) {
			int success = glfwInit();
			PN_CORE_ASSERT(success, "Could not initialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);
			GLFWInitialized__ = true;
		}

		window_ = glfwCreateWindow((int)props.Width, (int)props.Height, data_.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(window_);

		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		PN_CORE_ASSERT(status, "Failed to initialize Glad!");

		glfwSetWindowUserPointer(window_, &data_);
		SetVSync(true);

		// Set GLFW callbacks
			glfwSetWindowSizeCallback(window_, [](GLFWwindow* window, int width, int height) {
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.Width = width;
				data.Height = height;

				WindowResizeEvent event(width, height);
				data.EventCallback(event);// at this time this callback is already set up
			});
			glfwSetWindowCloseCallback(window_, [](GLFWwindow* window) {
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				WindowCloseEvent event;
				data.EventCallback(event);
			});
			glfwSetKeyCallback(window_, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				switch (action) {
					case GLFW_PRESS: {
						KeyPressedEvent event(key, 0);
						data.EventCallback(event);
						break;
					}
					case GLFW_RELEASE: {
						KeyReleasedEvent event(key);
						data.EventCallback(event);
						break;
					}
					case GLFW_REPEAT: {
						KeyPressedEvent event(key, 1);
						data.EventCallback(event);
						break;
					}
				}
			});
			glfwSetMouseButtonCallback(window_, [](GLFWwindow* window, int button, int action, int mods) {
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				switch (action) {
					case GLFW_PRESS: {
						MouseButtonPressedEvent event(button);
						data.EventCallback(event);
						break;
					}
					case GLFW_RELEASE: {
						MouseButtonReleasedEvent event(button);
						data.EventCallback(event);
						break;
					}
				}
			});
			glfwSetScrollCallback(window_, [](GLFWwindow* window, double xOffset, double yOffset) {
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				MouseScrolledEvent event((float)xOffset, (float)yOffset);
				data.EventCallback(event);
			});
			glfwSetCursorPosCallback(window_, [](GLFWwindow* window, double xPos, double yPos) {
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				MouseMovedEvent event((float)xPos, (float)yPos);
				data.EventCallback(event);
			});
		// ~Set GLFW callbacks
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(window_);
	}
};