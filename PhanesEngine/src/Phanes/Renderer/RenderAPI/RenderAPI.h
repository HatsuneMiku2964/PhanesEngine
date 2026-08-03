#pragma once

#include <glm/glm.hpp>

#include "Phanes/Renderer/VertexArray/VertexArray.h"

namespace Phanes
{
    class RenderAPI
    {
    public:
        enum class RendererAPI
        {
            None = 0,
            OpenGL = 1,
        };

    public:
        virtual void Clear() = 0;
        virtual void SetClearColor(const glm::vec4& color) = 0;

        pn_forceinline static RendererAPI GetAPI() { return API; }

        virtual void DrawIndexed(const Ref<VtxArr>& vao) = 0;

    private:
        static RendererAPI API;
    };

}
