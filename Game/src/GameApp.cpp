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

Phanes::Application* Phanes::CreateApplication()
{
	return new Sandbox();
}
