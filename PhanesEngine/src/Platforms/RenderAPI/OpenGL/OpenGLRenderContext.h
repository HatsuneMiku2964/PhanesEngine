#pragma once

#include "Phanes/Renderer/RenderContext.h"

struct GLFWwindow;

namespace Phanes
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

