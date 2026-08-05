#pragma once

#include "Phanes/Core/Renderer/RenderContext.h"

struct GLFWwindow;

namespace PN
{
    class OpenGLRenderContext : public RenderContext
    {
    public:
        OpenGLRenderContext(GLFWwindow* window);

        bool Init() override;
        bool Swap() override;

    private:
        GLFWwindow* window_handle;
    };
}

