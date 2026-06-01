#include "pnpch.h"
#include "Application.h"
#include <GLFW/glfw3.h>

namespace Phanes {

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	Application::Application() {
		window_ = std::unique_ptr<Window>(Window::Create());
		window_->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
	}
	Application::~Application() {

	}
	void Application::Run() {
		while (running_) {
			glClearColor(0, 0.5, 0.9, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			window_->OnUpdate();
		}
	}
	void Application::OnEvent(Event& e) {
		EventDispatcher dispatcher(e);

		// won't do anything if it's not a WindowCloseEvent
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
		PN_CORE_LOG_TRACE("{0}", e.ToString());
	}
	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		running_ = false;
		return true;
	}
}
