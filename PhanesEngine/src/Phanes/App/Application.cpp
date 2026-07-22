#include "pnpch.h"
#include "Application.h"

#include <glad/glad.h>

#include "Phanes/Events/EventsDispatch.h"

namespace Phanes
{
    Application* Application::instance = nullptr;

    Application::Application()
    {
        PN_CORE_LOG_WARN("Phanes Engine is lauched...");

        if (instance) {
            PN_CORE_LOG_ERROR("Assertion Failed: Application already exists!");
            __debugbreak();
        }

        instance = this;

        window = std::unique_ptr<Window>(Window::Create());
        window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

        imgui_layer = new ImGuiLayer();
        PushOverlay(imgui_layer);

        glGenVertexArrays(1, &vtx_arr);
        glBindVertexArray(vtx_arr);

        glGenBuffers(1, &vtx_buffer);
        glBindBuffer(GL_ARRAY_BUFFER, vtx_buffer);

        float vertices[9] = {
            -0.5f, -0.5f, 0.f,
             0.5f, -0.5f, 0.f,
             0.f,   0.5f, 0.f,
        };

        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), (const void*) &vertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

        unsigned int indices[3] = { 0, 1, 2 };

        glGenBuffers(1, &idx_buffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idx_buffer);

        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), (const void*) &indices, GL_STATIC_DRAW);
    }

    Application::~Application() { PN_CORE_LOG_INFO("Phanes Engine is closed"); }

    void Application::Run()
    {
        while (running) {
            glClearColor(0.4f, 0.55f, 0.9f, 1.f);
            glClear(GL_COLOR_BUFFER_BIT);

            glBindVertexArray(vtx_arr);
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

            for (Layer* layer : layerStack) layer->OnUpdate();

            imgui_layer->Begin();
            for (Layer* layer : layerStack) layer->OnImGuiRender();
            imgui_layer->End();

            window->OnUpdate();
            // auto [x, y] = Input::GetMousePos();
            // PN_CORE_LOG_TRACE("{0}, {1}", x, y);
        }
    }
    void Application::OnEvent(Event& e)
    {
        // PN_CORE_LOG_TRACE("{0}", e.ToString());

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