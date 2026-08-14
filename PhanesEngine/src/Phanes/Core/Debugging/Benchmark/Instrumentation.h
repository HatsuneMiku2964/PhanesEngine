#pragma once

// Basic instrumentation profiler by Cherno

// Usage: include this header file somewhere in your code (eg. precompiled header), and then use like:
//
// Instrumentor::Get().BeginSession("Session Name");        // Begin session 
// {
//     Timer timer("Profiled Scope Name");   // Place code like this in scopes you'd like to include in profiling
//     // Code
// }
// Instrumentor::Get().EndSession();                        // End Session
//
// You will probably want to macro-fy this, to switch on/off easily and use things like __FUNCSIG__ for the profile name.
//

#include <string>
#include <chrono>
#include <fstream>

namespace PN
{
    struct ProfileResult
    {
        std::string Name;
        long long Start, Dur;
        size_t ThreadID;
    };
    struct InstrumentationSession
    {
        std::string Name;
    };

    class Instrumentor
    {
    public:
        void BeginSession(const std::string& name, const std::string& filepath);
        void EndSession();

        void WriteProfile(const ProfileResult& result);
        void WriteHeader();
        void WriteFooter();

        pn_forceinline static Instrumentor* Get()
        {
            PN_CORE_ASSERT(instance, "Instrumentor instance does not exist!!!");
            return instance;
        }

    private:
        Instrumentor();

    private:
        static Instrumentor* instance;

        InstrumentationSession* current_session;
        std::ofstream ostream;
        int profile_cnt;
    };

    class Timer
    {
    public:
        Timer(const char* name);

        virtual ~Timer();

        void Stop();
    private:
        const char* name;
        std::chrono::time_point<std::chrono::high_resolution_clock> start_timepoint;
        bool stopped;
    };
}

#define ENABLE_PROFILING

#ifdef ENABLE_PROFILING
    #define PROFILE_BEGIN_SESSION(name, filepath) ::PN::Instrumentor::Get()->BeginSession(name, filepath);
    #define PROFILE_END_SESSION() ::PN::Instrumentor::Get()->EndSession();
    #define PROFILE_SCOPE(name) ::PN::Timer PN_TOKEN_CONCAT(timer, __LINE__)(name);
    #define PROFILE_FN() PROFILE_SCOPE(__FUNCSIG__);
#else
    #define PROFILE_SCOPE(name)
    #define PROFILE_FN()
    #define PROFILE_BEGIN_SESSION(name)
    #define PROFILE_END_SESSION()
#endif
