#include "pnpch.h"
#include "Application.h"

#include <GLFW/glfw3.h> // TODO: Remove it

#include "Phanes/Core/Events/EventsDispatch.h"

namespace PN
{
    Application* Application::instance = nullptr;

    Application::Application()
    {
        PN_CORE_LOG_WARN("Phanes Engine is lauched...");
        PN_CORE_ASSERT(!instance, "Assertion Failed: Application already exists!");
        instance = this;

        window = std::unique_ptr<Window>(Window::Create());
        window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
        window->SetVSync(false);

        imgui_layer = new ImGuiLayer();
        PushOverlay(imgui_layer);

        Renderer::Init();
    }
    Application::~Application() { PN_CORE_LOG_INFO("Phanes Engine is closed"); }

    void Application::Run()
    {
        while (running) {
            float time = (float) glfwGetTime(); // TODO: should change to sth like Platform::GetTime();
            time_step = time - last_frame_time;
            last_frame_time = time;

            if (!minimized) for (Layer* layer : layerStack) layer->OnUpdate(time_step);
            
            imgui_layer->Begin();
            for (Layer* layer : layerStack) layer->OnImGuiRender();
            imgui_layer->End();

            window->OnUpdate();
        }
    }
    void Application::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);

        e.Handled = dispatcher.Dispatch(BIND_EVENT_FN(OnWindowClose), BIND_EVENT_FN(OnWindowResize));

        for (auto it = layerStack.end(); it != layerStack.begin();) {
            (*--it)->OnEvent(e);
            if (e.Handled) break;
        }
    }

    bool Application::OnWindowClose(const WindowCloseEvent& e)
    {
        running = false;
        return true;
    }
    bool Application::OnWindowResize(const WindowResizeEvent& ev)
    {
        if (ev.GetHeight() == 0 || ev.GetWidth() == 0) {
            minimized = true;
            return false;
        } else {
            minimized = false;
            Renderer::OnWindowResized(ev.GetWidth(), ev.GetHeight());
            return false;
        }
    }
}
