#include "pnpch.h"
#include "Application.h"

#include "Phanes/Events/EventsDispatch.h"

namespace Phanes
{
    Application* Application::instance = nullptr;

    Application::Application()
    {
        PN_CORE_LOG_WARN("Phanes Engine is lauched...");
        PN_CORE_ASSERT(!instance, "Assertion Failed: Application already exists!");
        instance = this;

        window = std::unique_ptr<Window>(Window::Create());
        window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

        imgui_layer = new ImGuiLayer();
        PushOverlay(imgui_layer);
    }
    Application::~Application() { PN_CORE_LOG_INFO("Phanes Engine is closed"); }

    void Application::Run()
    {
        while (running) {
            
            for (Layer* layer : layerStack) layer->OnUpdate();

            imgui_layer->Begin();
            for (Layer* layer : layerStack) layer->OnImGuiRender();
            imgui_layer->End();

            window->OnUpdate();
        }
    }
    void Application::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);

        // Info: won't do anything if e is not a WindowCloseEvent
        e.Handled = dispatcher.Dispatch([this](WindowCloseEvent& ev) { return OnWindowClose(ev); });

        for (auto it = layerStack.end(); it != layerStack.begin();) {
            (*--it)->OnEvent(e);
            if (e.Handled) break;
        }
    }
    bool Application::OnWindowClose(WindowCloseEvent& e)
    {
        running = false;
        return true;
    }
}
