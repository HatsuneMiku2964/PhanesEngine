#pragma once

#include "Phanes/Core.h"

#include "Phanes/Events/AppEvents.h"
#include "Phanes/Events/Events.h"
#include "Phanes/Layer/LayerStack.h"
#include "Phanes/Window.h"

namespace Phanes
{
    class PN_API Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();
        void OnEvent(Event& e);

        bool OnWindowClose(const WindowCloseEvent& e);

        void PushLayer(Layer* layer) {
            layerStack_.PushLayer(layer);
        }
        void PushOverlay(Layer* overlay) {
            layerStack_.PushOverlay(overlay);
            overlay->OnAttach();
        }

        inline static Application& Get() { return *instance_; }
        inline Window& GetWindow() { return *window_; }

    private:
        std::unique_ptr<Window> window_;
        bool running_ = true;
        LayerStack layerStack_;
        static Application* instance_;
    };

    // TIP: Will be defined by clients
    Application* CreateApplication();
}