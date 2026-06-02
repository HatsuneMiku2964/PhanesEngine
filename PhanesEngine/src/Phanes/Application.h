#pragma once

#include "Phanes/Core.h"

#include "Phanes/Window.h"
#include "Phanes/Layer/LayerStack.h"
#include "Phanes/Events/Events.h"
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

		// pointless funcs for future extension
		void PushLayer(Layer* layer) { layerStack_.PushLayer(layer); }
		void PushOverlay(Layer* overlay) { layerStack_.PushOverlay(overlay); }
	private:
		std::unique_ptr<Window> window_;
		bool running_ = true;
		LayerStack layerStack_;
	};

	// Will be defined by clients
	Application* CreateApplication();
}