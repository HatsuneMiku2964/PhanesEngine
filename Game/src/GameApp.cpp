#include <Phanes.h>
#include <Phanes/Core/Entry.h>

#include "Sandbox2D.h"

class Sandbox : public PN::Application
{
public:
    Sandbox() { PushLayer(new Sandbox2D()); }
};

namespace PN
{
    Application* PN::CreateApplication() { return new Sandbox(); }
}
