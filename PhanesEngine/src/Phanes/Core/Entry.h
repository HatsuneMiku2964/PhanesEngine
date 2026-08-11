#pragma once

extern PN::Application* PN::CreateApplication();

int main(int argc, char** argv)
{
    PN::Log::Init();

    PN::Application* App = PN::CreateApplication();
    App->Run();
    delete App;
    return 0;
}
