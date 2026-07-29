#include "pnpch.h"
#include "Application.h"

#include "Phanes/Events/EventsDispatch.h"
#include "Phanes/Renderer/Renderer/Renderer.h"
#include "Phanes/Renderer/RenderCommand/RenderCommand.h"

namespace Phanes
{
    Application* Application::instance = nullptr;

    Application::Application()
        :camera(-1.6f, 1.6f, -0.9f, 0.9f)
    {
        PN_CORE_LOG_WARN("Phanes Engine is lauched...");
        PN_CORE_ASSERT(!instance, "Assertion Failed: Application already exists!");
        instance = this;

        window = std::unique_ptr<Window>(Window::Create());
        window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

        imgui_layer = new ImGuiLayer();
        PushOverlay(imgui_layer);

        vao.reset(VtxArr::Create());

        float vertices[] = {
            -0.5f, -0.5f,	1.f, 0.f, 0.f,
             0.5f, -0.5f,	0.f, 1.f, 0.f,
             0.f,   0.5f,	0.f, 0.f, 1.f,
        };
        std::shared_ptr<VtxBuffer> vbo;
        BufferLayout layout = {ShaderData::ShaderDataType::Float2, ShaderData::ShaderDataType::Float3};
        vbo.reset(VtxBuffer::Create(vertices, layout));

        uint32_t indices[3] = {0, 1, 2};
        std::shared_ptr<IdxBuffer> ibo;
        ibo.reset(IdxBuffer::Create(indices));

        shader.reset(new Shader("../Game/src/Shader.shader"));

        vao->AddVtxBuffer(vbo);
        vao->SetIdxBuffer(ibo);

        vao->Unbind();
    }

    Application::~Application() { PN_CORE_LOG_INFO("Phanes Engine is closed"); }

    void Application::Run()
    {
        while (running) {
            RenderCmd::SetClearColor({0.06f, 0.06f, 0.06f, 0.06f});
            RenderCmd::Clear();

            camera.SetPos({0.1f, 0.1f, 0.f});
            camera.SetRot(70.f);

            Renderer::BeginScene(camera);
            Renderer::Submit(shader, vao);
            Renderer::EndScene();

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
