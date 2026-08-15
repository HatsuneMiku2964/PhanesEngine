#pragma once

#include "Phanes/Core/Renderer/RenderAPI.h"

namespace PN
{
    class RenderCmd
    {
    public:
        pn_forceinline static void Init() { render_api->Init(); }
        pn_forceinline static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) { render_api->SetViewport(x, y, width, height); }

        pn_forceinline static void Clear() { render_api->Clear(); }
        pn_forceinline static void SetClearColor(const glm::vec4& color) { render_api->SetClearColor(color); }

        pn_forceinline static void DrawIndexed(const Ref<VtxArr>& vao, uint32_t idx_cnt = 0) { render_api->DrawIndexed(vao, idx_cnt); }
    private:
        static RenderAPI* render_api;
    };
}
