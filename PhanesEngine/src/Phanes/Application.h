#pragma once

#include "Core.h"
#include "Window.h"
#include "Phanes/Events/AppEvents.h"

namespace Phanes {
	class PN_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		void OnEvent(Event& e);

		bool OnWindowClose(WindowCloseEvent& e);
	private:
		std::unique_ptr<Window> window_;
		bool running_ = true;
	};

	// Will be defined by clients
	Application* CreateApplication();
}