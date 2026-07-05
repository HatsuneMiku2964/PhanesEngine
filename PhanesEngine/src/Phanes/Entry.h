#pragma once

#ifdef PN_PLATFORMS_WINDOWS
    extern Phanes::Application* Phanes::CreateApplication();

    int main(int argc, char** argv)
    {
        Phanes::Log::Init();
        PN_CORE_LOG_INFO("Phanes Engine is lauched...");

        Phanes::Application* App = Phanes::CreateApplication();
        App->Run();
        delete App;
        return 0;
    }
#else
    #error Phanes Engine only supports Windows!
#endif