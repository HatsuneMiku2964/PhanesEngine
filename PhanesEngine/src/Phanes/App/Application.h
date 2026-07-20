#pragma once

#include "Phanes/Core.h"

#include "Phanes/Window.h"
#include "Phanes/Events/Events.h"
#include "Phanes/Events/AppEvents.h"
#include "Phanes/Layer/LayerStack.h"
#include "Phanes/ImGui/ImGuiLayer.h"

namespace Phanes
{
    class PN_API Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();
        void OnEvent(Event& e);

        bool OnWindowClose(WindowCloseEvent& e);

        void PushLayer(Layer* layer) { layerStack_.PushLayer(layer); }
        void PushOverlay(Layer* overlay) { layerStack_.PushOverlay(overlay); }

        inline static Application& Get() { return *instance_; }
        inline Window& GetWindow() { return *window_; }

    private:
        bool running_ = true;

        LayerStack layerStack_;
        ImGuiLayer* imgui_layer;

        std::unique_ptr<Window> window_;

        static Application* instance_;
    };

    // INFO: Will be defined by clients
    Application* CreateApplication();
}