#include "pnpch.h"
#include "Application.h"
#include <GLFW/glfw3.h>

namespace Phanes {
	Application::Application() {
		Window__ = std::unique_ptr<Window>(Window::Create());
	}
	Application::~Application() {

	}
	void Application::Run() {
		while (Running__) {
			glClearColor(1, 1, 0, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			Window__->OnUpdate();
		}
	}
}
