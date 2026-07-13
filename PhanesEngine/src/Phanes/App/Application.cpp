#include "pnpch.h"
#include "Application.h"

#include <glad/glad.h>

#include "Phanes/Input.h"
#include "Phanes/Events/Dispatch/EventsDispatch.h"

namespace Phanes
{
    Application* Application::instance_ = nullptr;

    Application::Application()
    {
        if (instance_) {
            PN_CORE_LOG_ERROR("Assertion Failed: {0}", "Application already exists!");
            __debugbreak();
        }

        instance_ = this;

        window_ = std::unique_ptr<Window>(Window::Create());
        window_->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
    }

    Application::~Application() {}

    void Application::Run()
    {
        while (running_) {
            glClearColor(0.f, 0.5f, 0.9f, 1.f);
            glClear(GL_COLOR_BUFFER_BIT);

            for (Layer* layer : layerStack_) layer->OnUpdate();
            window_->OnUpdate();

            // auto [x, y] = Input::GetMousePos();
            // PN_CORE_LOG_TRACE("{0}, {1}", x, y);
        }
    }
    void Application::OnEvent(Event& e)
    {
        // PN_CORE_LOG_TRACE("{0}", e.ToString());

        EventDispatcher dispatcher(e);

        dispatcher.Dispatch([this](const WindowCloseEvent& ev) { return OnWindowClose(ev); });

        for (auto it = layerStack_.end(); it != layerStack_.begin();) {
            (*--it)->OnEvent(e);
            if (e.Handled) break;
        }
    }
    bool Application::OnWindowClose(const WindowCloseEvent& e)
    {
        running_ = false;
        return true;
    }
}