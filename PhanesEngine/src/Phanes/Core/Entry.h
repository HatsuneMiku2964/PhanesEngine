#pragma once

extern PN::Application* PN::CreateApplication();

int main(int argc, char** argv)
{
    PN::Application* App;
    {
        PROFILE_BEGIN_SESSION("Launching", "../Game/Launch.json");
        PN::Log::Init();
        App = PN::CreateApplication();
        PROFILE_END_SESSION();
    }
    {
        PROFILE_BEGIN_SESSION("Runtime", "../Game/Runtime.json");
        App->Run();
        PROFILE_END_SESSION();
    }
    {
        PROFILE_BEGIN_SESSION("Shutdown", "../Game/Shutdown.json");
        delete App;
        PROFILE_END_SESSION();
    }
    return 0;
}
