#pragma once

#include "Core.h"

namespace Phanes {
	class PN_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// Will be defined by clients
	Application* CreateApplication();
}

