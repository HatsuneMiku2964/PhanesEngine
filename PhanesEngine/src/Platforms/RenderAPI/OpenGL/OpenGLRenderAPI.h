#pragma once

#include "Phanes/Renderer/RenderAPI/RenderAPI.h"

namespace Phanes
{
    class OpenGLRenderAPI : public RenderAPI
    {
    public:
        void Clear() override;
        void SetClearColor(const glm::vec4& color) override;

        void DrawIndexed(const Ref<VtxArr> &vao) override;
    };
}
