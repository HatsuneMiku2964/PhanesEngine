#pragma once

#include "Renderer/RenderContext.h"

struct GLFWwindow;

namespace Phanes
{
    class OpenGLRenderContext : public RenderContext
    {
    public:
        OpenGLRenderContext(GLFWwindow* window);

        virtual bool Init() override;
        virtual bool Swap() override;

    private:
        GLFWwindow* window_handle;
    };
}

