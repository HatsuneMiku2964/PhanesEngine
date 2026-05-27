#pragma once

#ifdef PN_PLATFORMS_WINDOWS
	extern Phanes::Application* Phanes::CreateApplication();

	int main(int argc, char**argv) {
		Phanes::Log::Init();
		PN_CORE_WARN("Phanes Engine is lauched...");

		auto App = Phanes::CreateApplication();
		App->Run();
		delete App;
		return 0;
	}
#else
	#error Phanes Engine only supports Windows!
#endif