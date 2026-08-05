#pragma once

#ifdef PN_PLATFORMS_WINDOWS
// INFO: Will be defined by clients
    extern PN::Application* PN::CreateApplication();

    int main(int argc, char** argv)
    {
        PN::Log::Init();

        PN::Application* App = PN::CreateApplication();
        App->Run();
        delete App;
        return 0;
    }
#else
    #error PN Engine only supports Windows!
#endif