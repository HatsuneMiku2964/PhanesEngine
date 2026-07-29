#pragma once

#include "Phanes/Renderer/RenderAPI/RenderAPI.h"

namespace Phanes
{
    class RenderCmd
    {
    public:
        pn_forceinline static void Clear() { render_api->Clear(); }
        pn_forceinline static void SetClearColor(const glm::vec4& color) { render_api->SetClearColor(color); }

        pn_forceinline static void DrawIndexed(const std::shared_ptr<VtxArr>& vao) { render_api->DrawIndexed(vao); }
    private:
        static RenderAPI* render_api;
    };
}
