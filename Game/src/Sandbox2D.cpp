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

    PN::Renderer2D::ResetStat();
    PN::Renderer2D::BeginScene(camera_ctrl.GetCamera());
    {
        static constexpr int it_cnt = 30;

        float padding_ = 1.f + padding;
        for (int i = 0; i < it_cnt; ++i) for (int j = 0; j < it_cnt; ++j) {
            PN::Renderer2D::DrawQuad(
                {{1.f, 1.f}, rot, {(float) i * padding_, (float) j * padding_, 0.f}},
                color);
        }
        for (int i = 0; i < it_cnt; ++i) for (int j = 0; j < it_cnt; ++j) {
            PN::Renderer2D::DrawQuad({
                {1.f, 1.f}, rot, {(float) i * padding_, (float) j * padding_, 0.1f}},
                tex, tile_factor);
        }
    }
    PN::Renderer2D::EndScene();
    PN::Renderer2D::BeginScene(camera_ctrl.GetCamera());
    for (float y = -5.f; y < 5.f; y += 0.5f) for (float x = -5.f; x < 5.f; x += 0.5f)
        PN::Renderer2D::DrawQuad({{0.45f, 0.45f}, 0.f, {x+5.f, y - 7.f, 0.f}},
                                 {(y + 5.f) / 10.f, 0.4f, (x + 5.f) / 7.f, 1.f});
    PN::Renderer2D::EndScene();
}

void Sandbox2D::OnEvent(PN::Event& event)
{
    camera_ctrl.OnEvent(event);
}

void Sandbox2D::OnImGuiRender()
{
    ImGui::Begin("Settings");

    ImGui::ColorEdit4("Color", glm::value_ptr(color));
    ImGui::DragFloat("tile factor", &tile_factor, 0.01f, 0.5f, 5.f);
    ImGui::DragFloat("padding", &padding, 0.001f, 0.f, 1.f);
    ImGui::DragFloat("rotation", &rot, 0.5f, 0.f, 180.f);

    auto& stat = PN::Renderer2D::GetStats();
    ImGui::Text("Renderer Stats: ");
    ImGui::Text("Draw calls: %u", stat.DrawCallCnt);
    ImGui::Text("Quads: %u", stat.QuadCnt);
    ImGui::Text("Vertices: %u", stat.GetVtxCnt());
    ImGui::Text("Indices: %u", stat.GetIdxCnt());
    ImGui::End();
}
