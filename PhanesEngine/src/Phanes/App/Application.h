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

        void PushLayer(Layer* layer) { layerStack.PushLayer(layer); }
        void PushOverlay(Layer* overlay) { layerStack.PushOverlay(overlay); }

        inline static Application& Get() { return *instance; }
        inline Window& GetWindow() { return *window; }

    private:
        unsigned int vtx_arr, vtx_buffer, idx_buffer;

        bool running = true;

        LayerStack layerStack;
        ImGuiLayer* imgui_layer;

        std::unique_ptr<Window> window;

        static Application* instance;
    };

    // INFO: Will be defined by clients
    Application* CreateApplication();
}