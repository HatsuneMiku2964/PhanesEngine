#pragma once
#ifdef PN_PLATFORMS_WINDOWS
#include <stdio.h>
extern Phanes::Application* Phanes::CreateApplication();
int main(int argc, char**argv) {
	printf("Phanes Engine Starting...\n");
	auto App = Phanes::CreateApplication();
	App->Run();
	delete App;
	return 0;
}
#endif