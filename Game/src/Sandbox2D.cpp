#include "Sandbox2D.h"

#include <imgui/imgui.h>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
    : Layer("Sandbox2D")
{
}

void Sandbox2D::OnAttach()
{
    tex = PN::Texture2D::Create("../Game/Assets/Textures/alphatest.png");
}

void Sandbox2D::OnDetach() {}

void Sandbox2D::OnUpdate(PN::TimeStep ts)
{
    TRACK(Sandbox2D::OnUpdate);
    {
        TRACK("OrthoCameraController::OnUpdate");
        camera_ctrl.OnUpdate(ts);
    }

    PN::RenderCmd::SetClearColor({0.06f, 0.06f, 0.06f, 0.06f});
    PN::RenderCmd::Clear();

    {
        TRACK("Render Draw");
        PN::Renderer2D::BeginScene(camera_ctrl.GetCamera());

        static constexpr int it_cnt = 10;
        for (int i = 0; i < it_cnt; ++i) {
            for (int j = 0; j < it_cnt; ++j) {
                PN::Renderer2D::DrawQuad({(float) i, (float) j, 0.01f}, {1.5f, 1.5f}, {color, 1.f});
            }
        }
        for (int i = 0; i < it_cnt; ++i) {
            for (int j = 0; j < it_cnt; ++j) {
                PN::Renderer2D::DrawQuad({(float) i, (float) j, 0.1f}, {1.f, 1.f}, tex);
            }
        }
        PN::Renderer2D::EndScene();
    }
}

void Sandbox2D::OnEvent(PN::Event& event)
{
    camera_ctrl.OnEvent(event);
}

void Sandbox2D::OnImGuiRender()
{
    ImGui::Begin("Settings");
    ImGui::ColorEdit3("Color", glm::value_ptr(color));
    for (profile_res res : profiles_vector)
    {
        char name[50];
        strcpy_s(name, "%.3fms");
        strcat_s(name, res.name);

        ImGui::Text((const char*) name, res.time);
    }
    profiles_vector.clear();
    ImGui::End();
}
