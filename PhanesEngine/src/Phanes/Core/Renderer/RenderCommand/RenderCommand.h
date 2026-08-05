#pragma once

#include "Phanes/Core/Renderer/RenderAPI.h"

namespace PN
{
    class RenderCmd
    {
    public:
        pn_forceinline static void Init() { render_api->Init(); }

        pn_forceinline static void Clear() { render_api->Clear(); }
        pn_forceinline static void SetClearColor(const glm::vec4& color) { render_api->SetClearColor(color); }

        pn_forceinline static void DrawIndexed(const Ref<VtxArr>& vao) { render_api->DrawIndexed(vao); }
    private:
        static RenderAPI* render_api;
    };
}
