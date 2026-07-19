#include "pnpch.h"

#include <Phanes.h>
#include <imgui/imgui.h>

#include "Phanes/Layer/Layer.h"

class Sandbox : public Phanes::Application
{
public:
    Sandbox() { PushLayer(new Phanes::Layer()); }
};

namespace Phanes
{
    Application* Phanes::CreateApplication() { return new Sandbox(); }
}
