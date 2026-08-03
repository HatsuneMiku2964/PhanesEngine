#include "pnpch.h"

#include <Phanes.h>
#include <imgui/imgui.h>
#include <glm/ext/matrix_transform.hpp>
#include <Platforms/RenderAPI/OpenGL/OpenGLShader.h>

class SampleLayer : public Phanes::Layer
{
public:
    SampleLayer()
        :Layer("sample layer"), camera(-1.6f, 1.6f, -0.9f, 0.9f)
    {
        vao.reset(Phanes::VtxArr::Create());

        float vertices[] = {
            -0.5f, -0.5f,
             0.5f, -0.5f,
             0.f,   0.5f,
        };
        Phanes::Ref<Phanes::VtxBuffer> vbo;
        Phanes::BufferLayout layout = {
            Phanes::ShaderData::ShaderDataType::Float2,
        };
        vbo.reset(Phanes::VtxBuffer::Create(vertices, layout));

        uint32_t indices[3] = {0, 1, 2};
        Phanes::Ref<Phanes::IdxBuffer> ibo;
        ibo.reset(Phanes::IdxBuffer::Create(indices));

        shader.reset(Phanes::Shader::Create("../Game/src/Shader.shader"));

        vao->AddVtxBuffer(vbo);
        vao->SetIdxBuffer(ibo);

        vao->Unbind();
    }

    void OnImGuiRender() override
    {
        ImGui::Begin("Settings");
        ImGui::ColorEdit3("triangle color", glm::value_ptr(color));
        ImGui::End();
    }

    void OnUpdate(Phanes::TimeStep ts) override
    {
        PN_LOG_TRACE("Delta time: {0}s ({1}ms)", ts.Secs(), ts.MiliSecs());

        Phanes::RenderCmd::SetClearColor({0.06f, 0.06f, 0.06f, 0.06f});
        Phanes::RenderCmd::Clear();

        float time = (float) ts;

        if (Phanes::Input::IsKeyPressed(PN_KEY_A)) pos.x -= speed * time;
        if (Phanes::Input::IsKeyPressed(PN_KEY_D)) pos.x += speed * time;
        if (Phanes::Input::IsKeyPressed(PN_KEY_S)) pos.y -= speed * time;
        if (Phanes::Input::IsKeyPressed(PN_KEY_W)) pos.y += speed * time;

        if (Phanes::Input::IsKeyPressed(PN_KEY_Q)) rot -= rot_rate * time;
        if (Phanes::Input::IsKeyPressed(PN_KEY_E)) rot += rot_rate * time;

        if (Phanes::Input::IsKeyPressed(PN_KEY_UP))     tri_pos.y += speed * time;
        if (Phanes::Input::IsKeyPressed(PN_KEY_DOWN))   tri_pos.y -= speed * time;
        if (Phanes::Input::IsKeyPressed(PN_KEY_LEFT))   tri_pos.x -= speed * time;
        if (Phanes::Input::IsKeyPressed(PN_KEY_RIGHT))  tri_pos.x += speed * time;

        camera.SetPos({pos, 0.f});
        camera.SetRot(rot);

        std::dynamic_pointer_cast<Phanes::OpenGLShader>(shader)->SetUniform("u_color", color);

        glm::mat4 transform = glm::translate(glm::mat4(1.f), glm::vec3(tri_pos, 0.f));

        Phanes::Renderer::BeginScene(camera);
        Phanes::Renderer::Submit(shader, vao, transform);
        Phanes::Renderer::EndScene();
    }

private:
    Phanes::OrthographicCamera camera;
    Phanes::Ref<Phanes::Shader> shader;
    Phanes::Ref<Phanes::VtxArr> vao;

    glm::vec2 pos = {0.f, 0.f};
    glm::vec2 tri_pos = {0.f, 0.f};

    glm::vec3 color = {0.2f, 0.1f, 1.f};

    float rot = 0.f;
    float rot_rate = 100.f;
    float speed = 2.f;
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
