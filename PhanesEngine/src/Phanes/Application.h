#pragma once

#include "Core.h"
#include "Window.h"

namespace Phanes {
	class PN_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	private:
		std::unique_ptr<Window> Window__;
		bool Running__ = true;
	};

	// Will be defined by clients
	Application* CreateApplication();
}

