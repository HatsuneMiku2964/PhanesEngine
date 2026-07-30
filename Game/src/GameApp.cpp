#include "pnpch.h"

#include <Phanes.h>
#include <imgui/imgui.h>

#include "Phanes/Layer/Layer.h"

class SampleLayer : public Phanes::Layer
{
public:
    SampleLayer()
        :Layer("sample layer"), camera(-1.6f, 1.6f, -0.9f, 0.9f)
    {
        vao.reset(Phanes::VtxArr::Create());

        float vertices[] = {
            -0.5f, -0.5f,	1.f, 0.f, 0.f,
             0.5f, -0.5f,	0.f, 1.f, 0.f,
             0.f,   0.5f,	0.f, 0.f, 1.f,
        };
        std::shared_ptr<Phanes::VtxBuffer> vbo;
        Phanes::BufferLayout layout = {
            Phanes::ShaderData::ShaderDataType::Float2,
            Phanes::ShaderData::ShaderDataType::Float3,
        };
        vbo.reset(Phanes::VtxBuffer::Create(vertices, layout));

        uint32_t indices[3] = {0, 1, 2};
        std::shared_ptr<Phanes::IdxBuffer> ibo;
        ibo.reset(Phanes::IdxBuffer::Create(indices));

        shader.reset(new Phanes::Shader("../Game/src/Shader.shader"));

        vao->AddVtxBuffer(vbo);
        vao->SetIdxBuffer(ibo);

        vao->Unbind();
    }

    void OnImGuiRender() override
    {
        ImGui::Begin("Test");
        ImGui::Text("Test window");
        ImGui::End();
    }

    void OnUpdate() override
    {
        Phanes::RenderCmd::SetClearColor({0.06f, 0.06f, 0.06f, 0.06f});
        Phanes::RenderCmd::Clear();

        if (Phanes::Input::IsKeyPressed(PN_KEY_A)) pos.x -= speed;
        if (Phanes::Input::IsKeyPressed(PN_KEY_D)) pos.x += speed;
        if (Phanes::Input::IsKeyPressed(PN_KEY_S)) pos.y -= speed;
        if (Phanes::Input::IsKeyPressed(PN_KEY_W)) pos.y += speed;
        if (Phanes::Input::IsKeyPressed(PN_KEY_Q)) rot -= rot_rate;
        if (Phanes::Input::IsKeyPressed(PN_KEY_E)) rot += rot_rate;

        camera.SetPos({pos, 0.f});
        camera.SetRot(rot);

        Phanes::Renderer::BeginScene(camera);
        Phanes::Renderer::Submit(shader, vao);
        Phanes::Renderer::EndScene();
    }

private:
    Phanes::OrthographicCamera camera;
    std::shared_ptr<Phanes::Shader> shader;
    std::shared_ptr<Phanes::VtxArr> vao;

    glm::vec2 pos = {0.f, 0.f};
    float rot = 0.f;
    float rot_rate = glm::radians(20.f);
    float speed = 0.01f;
};

class Sandbox : public Phanes::Application
{
public:
    Sandbox() { PushLayer(new SampleLayer()); }
};

namespace Phanes
{
    Application* Phanes::CreateApplication() { return new Sandbox(); }
}
