#include <Phanes.h>

class test : public Phanes::Layer {
	public:
	test() : Layer("test") {}
	~test() {}

	void OnUpdate() override
	{
		PN_CORE_LOG_INFO("test layer update");
	}
};



class Sandbox : public Phanes::Application
{
public:
	Sandbox() 
	{
		PushLayer(new test());
	}
	~Sandbox()
	{

	}
};

namespace Phanes {
	Phanes::Application* Phanes::CreateApplication() { return new Sandbox(); }
}
