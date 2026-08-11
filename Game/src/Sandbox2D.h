#pragma once

#include <Phanes.h>
#include <chrono>

template<typename Fn>
class Timer
{
public:
    Timer(const char* name, Fn&& fn)
        :name(name), fn(fn)
    {
        start = std::chrono::high_resolution_clock::now();
    }
    ~Timer() { if (!stopped) Stop(); }

    void Stop()
    {
        stopped = true;
        auto end = std::chrono::high_resolution_clock::now();

        long long start_time = std::chrono::time_point_cast<std::chrono::microseconds>(start).time_since_epoch().count();
        long long end_time = std::chrono::time_point_cast<std::chrono::microseconds>(end).time_since_epoch().count();

        float time = (end_time - start_time) * 0.001f;

        fn({name, time});
    }
private:
    const char* name;
    std::chrono::time_point<std::chrono::steady_clock> start;
    Fn fn;
    bool stopped = false;
};
#define TRACK(name) Timer timer##__FILE__##__LINE__(#name, [&](profile_res profile) { profiles_vector.push_back(profile); });

class Sandbox2D : public PN::Layer
{
public:
    Sandbox2D();
    ~Sandbox2D() override = default;

    void OnAttach() override;
    void OnDetach() override;

    void OnUpdate(PN::TimeStep ts) override;
    void OnEvent(PN::Event& event) override;
    void OnImGuiRender() override;

private:
    PN::OrthoCameraController camera_ctrl;

    PN::Ref<PN::VtxArr> vao;
    PN::Ref<PN::Shader> shader;
    PN::Ref<PN::Texture2D> tex;

    struct profile_res
    {
        const char* name;
        float time;
    };
    std::vector<profile_res> profiles_vector;

    glm::vec3 color = {0.2f, 0.1f, 1.f};
};

