#pragma once

#include "Phanes/Core/Renderer/RenderAPI.h"

namespace PN
{
    class OpenGLRenderAPI : public RenderAPI
    {
    public:
        void Init() override;

        void Clear() override;
        void SetClearColor(const glm::vec4& color) override;

        void DrawIndexed(const Ref<VtxArr> &vao) override;
    };
}
