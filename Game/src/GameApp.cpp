#include "pnpch.h"

#include <Phanes.h>
#include <imgui/imgui.h>

#include "Phanes/Layer/Layer.h"
#include "Phanes/Events/Events.h"

class SampleLayer : public Phanes::Layer
{
public:
    void OnImGuiRender() override
    {
        ImGui::Begin("Test");
        ImGui::Text("Test window");
        ImGui::End();
    }
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
