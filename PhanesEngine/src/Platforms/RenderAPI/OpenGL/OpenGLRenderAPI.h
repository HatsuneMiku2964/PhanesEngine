#pragma once

#include "Phanes/Core/Renderer/RenderAPI.h"

namespace PN
{
    class OpenGLRenderAPI : public RenderAPI
    {
    public:
        void Init() override;
        void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;

        void Clear() override;
        void SetClearColor(const glm::vec4& color) override;

        void DrawIndexed(const Ref<VtxArr> &vao, uint32_t idx_cnt = 0) override;
    };
}
