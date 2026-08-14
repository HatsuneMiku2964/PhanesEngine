#pragma once

#include "Phanes/Core/Core.h"

#include "Phanes/Core/Window.h"
#include "Phanes/ImGui/ImGuiLayer.h"
#include "Phanes/Core/Events/Events.h"
#include "Phanes/Core/Events/AppEvents.h"
#include "Phanes/Core/Layer/LayerStack.h"

namespace PN
{
    class Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();
        void OnEvent(Event& e);

        pn_forceinline void PushLayer(Layer* layer) { layer_stack.PushLayer(layer); }
        pn_forceinline void PushOverlay(Layer* overlay) { layer_stack.PushOverlay(overlay); }

        pn_forceinline static Application& Get() { return *instance; }
        pn_forceinline Window& GetWindow() { return *window; }

    protected:
        bool OnWindowClose(const WindowCloseEvent& e);
        bool OnWindowResize(const WindowResizeEvent & ev);

    private:
        void Init();
        void Shutdown();

    private:
        static Application* instance;
        Ref<Window> window;

        LayerStack layer_stack;
        ImGuiLayer* imgui_layer;

        TimeStep time_step = 0.f;
        float last_frame_time = 0.f;

        bool running = true;
        bool minimized = false;
    };

    Application* CreateApplication();
}
