#include "pnpch.h"

#include <Phanes.h>
#include <imgui/imgui.h>
#include <glm/ext/matrix_transform.hpp>
#include <Platforms/RenderAPI/OpenGL/OpenGLShader.h>

class SampleLayer : public PN::Layer
{
public:
    SampleLayer()
        :Layer("sample layer"), camera(-1.6f, 1.6f, -0.9f, 0.9f)
    {
        vao.reset(PN::VtxArr::Create());

        float vertices[] = {
            -0.5f, -0.5f, 0.f, 0.f, 
             0.5f, -0.5f, 1.f, 0.f, 
             0.5f,  0.5f, 1.f, 1.f, 
            -0.5f,  0.5f, 0.f, 1.f, 
        };
        PN::Ref<PN::VtxBuffer> vbo;
        PN::BufferLayout layout = {
            PN::ShaderData::ShaderDataType::Float2,
            PN::ShaderData::ShaderDataType::Float2,
        };
        vbo.reset(PN::VtxBuffer::Create(vertices, layout));

        uint32_t indices[] = {0, 1, 2, 2, 3, 0};
        PN::Ref<PN::IdxBuffer> ibo;
        ibo.reset(PN::IdxBuffer::Create(indices));

        shader.reset(PN::Shader::Create("../Game/Assets/Shaders/Shader.shader")); 
        
        tex = PN::Texture2D::Create("../Game/Assets/Textures/tex.png");
        background = PN::Texture2D::Create("../Game/Assets/Textures/background.png");

        vao->AddVtxBuffer(vbo);
        vao->SetIdxBuffer(ibo);

        vao->Unbind();
    }

    void OnImGuiRender() override
    {
        ImGui::Begin("Settings");
        ImGui::ColorEdit3("Color", glm::value_ptr(color));
        ImGui::End();
    }

    void OnUpdate(PN::TimeStep ts) override
    {
        PN::RenderCmd::SetClearColor({0.06f, 0.06f, 0.06f, 0.06f});
        PN::RenderCmd::Clear();

        float time = (float) ts;
        {
            if (PN::Input::IsKeyPressed(PN_KEY_A)) pos.x -= speed * time;
            if (PN::Input::IsKeyPressed(PN_KEY_D)) pos.x += speed * time;
            if (PN::Input::IsKeyPressed(PN_KEY_S)) pos.y -= speed * time;
            if (PN::Input::IsKeyPressed(PN_KEY_W)) pos.y += speed * time;

            if (PN::Input::IsKeyPressed(PN_KEY_Q)) rot -= rot_rate * time;
            if (PN::Input::IsKeyPressed(PN_KEY_E)) rot += rot_rate * time;

            if (PN::Input::IsKeyPressed(PN_KEY_UP))     tri_pos.y += speed * time;
            if (PN::Input::IsKeyPressed(PN_KEY_DOWN))   tri_pos.y -= speed * time;
            if (PN::Input::IsKeyPressed(PN_KEY_LEFT))   tri_pos.x -= speed * time;
            if (PN::Input::IsKeyPressed(PN_KEY_RIGHT))  tri_pos.x += speed * time;
        }
        camera.SetPos({pos, 0.f});
        camera.SetRot(rot);

        //std::dynamic_pointer_cast<PN::OpenGLShader>(shader)->SetUniform("u_color", color);
        std::dynamic_pointer_cast<PN::OpenGLShader>(shader)->SetUniform("u_tex", 0);

        glm::mat4 transform = glm::translate(glm::mat4(1.f), glm::vec3(tri_pos, 0.f));

        PN::Renderer::BeginScene(camera);
        tex->Bind();
        PN::Renderer::Submit(shader, vao, transform);
        background->Bind();
        PN::Renderer::Submit(shader, vao, glm::translate(glm::mat4(1.f), glm::vec3(0.4f, 0.2f, 0.f)));
        PN::Renderer::EndScene();
    }

private:
    PN::OrthographicCamera camera;
    PN::Ref<PN::Shader> shader;
    PN::Ref<PN::VtxArr> vao;

    PN::Ref<PN::Texture2D> tex, background;

    glm::vec2 pos = {0.f, 0.f};
    glm::vec2 tri_pos = {0.f, 0.f};

    glm::vec3 color = {0.2f, 0.1f, 1.f};

    float rot = 0.f;
    float rot_rate = 100.f;
    float speed = 2.f;
};

class Sandbox : public PN::Application
{
public:
    Sandbox() { PushLayer(new SampleLayer()); }
};

namespace PN
{
    Application* PN::CreateApplication() { return new Sandbox(); }
}
