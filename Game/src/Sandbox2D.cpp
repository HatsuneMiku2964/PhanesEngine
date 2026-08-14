#include "Sandbox2D.h"

#include <imgui/imgui.h>
#include <glm/gtc/type_ptr.hpp>

#include "Phanes/Core/Debugging/Benchmark/Instrumentation.h"

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
    PROFILE_FN();

    camera_ctrl.OnUpdate(ts);

    PN::RenderCmd::SetClearColor({0.06f, 0.06f, 0.06f, 1.f});
    PN::RenderCmd::Clear();

    PN::Renderer2D::BeginScene(camera_ctrl.GetCamera());

    static constexpr int it_cnt = 20;

    for (int i = 0; i < it_cnt; ++i) {
        for (int j = 0; j < it_cnt; ++j) {
            PN::Renderer2D::DrawQuad({(float) i * 1.01f, (float) j * 1.01f}, {1.0f, 1.0f}, {color, 1.f});
        }
    }
    for (int i = 0; i < it_cnt; ++i) {
        for (int j = 0; j < it_cnt; ++j) {
            PN::Renderer2D::DrawQuad({(float) i * 1.01f, (float) j * 1.01f, 0.1f}, {1.f, 1.f}, tex, tile_factor);
        }
    }
    PN::Renderer2D::EndScene();
}

void Sandbox2D::OnEvent(PN::Event& event)
{
    camera_ctrl.OnEvent(event);
}

void Sandbox2D::OnImGuiRender()
{
    ImGui::Begin("Settings");
    ImGui::ColorEdit3("Color", glm::value_ptr(color));
    ImGui::DragFloat("tile factor", &tile_factor, 0.1f, 0.f, 10.f);
    ImGui::End();
}
