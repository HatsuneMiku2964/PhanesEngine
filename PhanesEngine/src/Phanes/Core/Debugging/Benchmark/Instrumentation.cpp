#include "pnpch.h"
#include "Instrumentation.h"

#include <thread>
#include <algorithm>

namespace PN
{
    Instrumentor* Instrumentor::instance = new Instrumentor();

    Instrumentor::Instrumentor()
        : current_session(nullptr), profile_cnt(0)
    {
    }

    void Instrumentor::BeginSession(const std::string& name, const std::string& filepath)
    {
        ostream.open(filepath), "failed to open file!!";
        WriteHeader();
        current_session = new InstrumentationSession{name};
    }

    void Instrumentor::EndSession()
    {
        WriteFooter();
        ostream.close();
        delete current_session;
        current_session = nullptr;
        profile_cnt = 0;
    }

    void Instrumentor::WriteHeader()
    {
        ostream << "{\"otherData\": {},\"traceEvents\":[";
        ostream.flush();
    }
    void Instrumentor::WriteProfile(const ProfileResult& result)
    {
        if (profile_cnt++ > 0) ostream << ",";

        std::string name = result.Name;
        std::ranges::replace(name, '"', '\'');

        ostream << "{";
        ostream << "\"cat\":\"function\",";
        ostream << "\"dur\":" << (result.End - result.Start) << ',';
        ostream << "\"name\":\"" << name << "\",";
        ostream << "\"ph\":\"X\",";
        ostream << "\"pid\":0,";
        ostream << "\"tid\":" << result.ThreadID << ",";
        ostream << "\"ts\":" << result.Start;
        ostream << "}";

        ostream.flush();
    }
    void Instrumentor::WriteFooter()
    {
        ostream << "]}";
        ostream.flush();
    }

}

namespace PN
{
    Timer::Timer(const char* name)
        : name(name), stopped(false)
    {
        start_timepoint = std::chrono::high_resolution_clock::now();
    }

    Timer::~Timer() { if (!stopped) Stop(); }
    void Timer::Stop() {
        auto endTimepoint = std::chrono::high_resolution_clock::now();

        long long start = std::chrono::time_point_cast<std::chrono::microseconds>(start_timepoint).time_since_epoch().count();
        long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

        size_t threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());
        Instrumentor::Get()->WriteProfile({name, start, end, threadID});

        stopped = true;
    }

}
