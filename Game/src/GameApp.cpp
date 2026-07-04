#include "pnpch.h"

#include <Phanes.h>
#include "Phanes/Layer/Layer.h"

class Sandbox : public Phanes::Application
{
public:
    Sandbox() {
        PushLayer(new Phanes::Layer());
        PushOverlay(new Phanes::ImGuiLayer());
    }
    ~Sandbox() {

    }
};

namespace Phanes
{
    Phanes::Application* Phanes::CreateApplication() {
        return new Sandbox();
    }
}
