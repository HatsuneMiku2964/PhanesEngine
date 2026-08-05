#pragma once

namespace PN
{
    class TimeStep
    {
    public:
        TimeStep(float time = 0.f)
            : delta(time)
        {
        }

        pn_forceinline explicit operator float() const noexcept { return delta; } 

        pn_forceinline float Secs() const { return delta; }
        pn_forceinline float MiliSecs() const { return delta * 1000.f; }

    private:
        float delta = 0.f;
    };
}
