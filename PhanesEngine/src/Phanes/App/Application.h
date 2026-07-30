#pragma once

#include "Phanes/Core.h"

#include "Phanes/Window.h"
#include "Phanes/Events/Events.h"
#include "Phanes/Events/AppEvents.h"
#include "Phanes/Layer/LayerStack.h"
#include "Phanes/ImGui/ImGuiLayer.h"

namespace Phanes
{

    class Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();
        void OnEvent(Event& e);

        bool OnWindowClose(WindowCloseEvent& e);

        pn_forceinline void PushLayer(Layer* layer) { layerStack.PushLayer(layer); }
        pn_forceinline void PushOverlay(Layer* overlay) { layerStack.PushOverlay(overlay); }

        pn_forceinline static Application& Get() { return *instance; }
        pn_forceinline Window& GetWindow() { return *window; }

    private:
        

        bool running = true;

        LayerStack layerStack;
        ImGuiLayer* imgui_layer;

        std::unique_ptr<Window> window;

        static Application* instance;
    };

    // INFO: Will be defined by clients
    Application* CreateApplication();
}
