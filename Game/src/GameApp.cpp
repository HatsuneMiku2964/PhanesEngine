#include <Phanes.h>

class test : public Phanes::Layer {
	public:
	test() : Layer("test") {}
	~test() {}	

	void OnUpdate() override
	{
		
	}
};



class Sandbox : public Phanes::Application
{
public:
	Sandbox() 
	{
		PushLayer(new test());
		PushOverlay ( new Phanes::ImGuiLayer ( ) );
	}
	~Sandbox()
	{

	}
};

namespace Phanes {
	Phanes::Application* Phanes::CreateApplication() { return new Sandbox(); }
}
