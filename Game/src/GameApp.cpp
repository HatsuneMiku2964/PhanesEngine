#include "pnpch.h"

#include <Phanes.h>
#include "Phanes/Layer/Layer.h"

class SampleLayer : public Phanes::Layer
{
public:
    void OnUpdate() override
    {
        //if (Phanes::Input::IsKeyPressed(PN_KEY_TAB))
        //    PN_CORE_LOG_TRACE("{0}", "tab is pressed!");
    }
};

class Sandbox : public Phanes::Application
{
public:
    Sandbox()
    {
        PushLayer(new SampleLayer());
        PushOverlay(new Phanes::ImGuiLayer());
    }
    ~Sandbox()
    {

    }
};

namespace Phanes
{
    Application* Phanes::CreateApplication()
    {
        return new Sandbox();
    }
}
