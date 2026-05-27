#include <Phanes.h>

class Sandbox : public Phanes::Application
{
public:
	Sandbox() 
	{

	}
	~Sandbox()
	{

	}
};

namespace Phanes {
	Phanes::Application* Phanes::CreateApplication() { return new Sandbox(); }
}
