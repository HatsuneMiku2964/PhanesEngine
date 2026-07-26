#include "pnpch.h"
#include "Application.h"

#include <glad/glad.h>

#include "Phanes/Events/EventsDispatch.h"
#include "Phanes/Renderer/Buffer/Buffer.h"

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

        vtx_arr.reset(VtxArr::Create());

        float vertices[] = {
            -0.35f, -0.5f,	1.f, 0.f, 0.f,
             0.35f, -0.5f,	0.f, 1.f, 0.f,
             0.f,   0.5f,	0.f, 0.f, 1.f,
        };
        std::shared_ptr<VtxBuffer> vtx_buffer;
        BufferLayout layout = { ShaderData::ShaderDataType::Float2, ShaderData::ShaderDataType::Float3 };
        vtx_buffer.reset(VtxBuffer::Create(vertices, layout));
        
        uint32_t indices[3] = { 0, 1, 2 };
        std::shared_ptr<IdxBuffer> idx_buffer;
        idx_buffer.reset(IdxBuffer::Create(indices));

        shader.reset(new Shader("../Game/src/Shader.shader"));

        vtx_arr->AddVtxBuffer(vtx_buffer);
        vtx_arr->SetIdxBuffer(idx_buffer);

        vtx_arr->Unbind();
    }

    Application::~Application() { PN_CORE_LOG_INFO("Phanes Engine is closed"); }

    void Application::Run()
    {
        while (running) {
            glClearColor(0.4f, 0.55f, 0.9f, 1.f);
            glClear(GL_COLOR_BUFFER_BIT);

            shader->Bind();
            vtx_arr->Bind();

            glDrawElements(GL_TRIANGLES, vtx_arr->GetIdxBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

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
