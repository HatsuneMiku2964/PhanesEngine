#pragma once

namespace PN
{
    class RenderContext
    {
    public:
        virtual bool Init() = 0;
        virtual bool Swap() = 0;
    };
}

