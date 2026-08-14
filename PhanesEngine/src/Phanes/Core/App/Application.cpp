#include "pnpch.h"
#include "Application.h"

#include <GLFW/glfw3.h> // TODO: Remove it

#include "Phanes/Core/Events/EventsDispatch.h"

namespace PN
{
    Application* Application::instance = nullptr;

    Application::Application() { Init(); }
    Application::~Application() { Shutdown(); }

    void Application::Init()
    {
        PROFILE_FN();

        PN_CORE_ASSERT(!instance, "Assertion Failed: Application already exists!");
        instance = this;

        window = std::unique_ptr<Window>(Window::Create());
        window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
        window->SetVSync(false);

        Renderer::Init();

        imgui_layer = new ImGuiLayer();
        PushOverlay(imgui_layer);
    }
    void Application::Shutdown() { PROFILE_FN(); }

    void Application::Run()
    {
        PROFILE_FN();

        while (running)
        {
            float time = (float) glfwGetTime(); // TODO: should change to sth like Platform::GetTime();
            time_step = time - last_frame_time;
            last_frame_time = time;
            {
                PROFILE_SCOPE("Layers update");
                if (!minimized) for (Layer* layer : layer_stack) layer->OnUpdate(time_step);
            }
            {
                PROFILE_SCOPE("Layers OnImGuiRender");
                imgui_layer->Begin();
                for (Layer* layer : layer_stack) layer->OnImGuiRender();
                imgui_layer->End();
            }
            window->OnUpdate();
        }
    }
    void Application::OnEvent(Event& e)
    {
        PROFILE_FN();
        EventDispatcher dispatcher(e);

        e.Handled = dispatcher.Dispatch(BIND_EVENT_FN(OnWindowClose), BIND_EVENT_FN(OnWindowResize));

        for (auto it = layer_stack.end(); it != layer_stack.begin();) {
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
