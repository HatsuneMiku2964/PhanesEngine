#pragma once

#include <glm/glm.hpp>

#include "Phanes/Core/Renderer/VertexArray/VertexArray.h"

namespace PN
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
        virtual void Init() = 0;
        virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;

        virtual void Clear() = 0;
        virtual void SetClearColor(const glm::vec4& color) = 0;

        pn_forceinline static RendererAPI GetAPI() { return API; }

        virtual void DrawIndexed(const Ref<VtxArr>& vao) = 0;

    private:
        inline static RendererAPI API = RendererAPI::OpenGL;
    };

}
