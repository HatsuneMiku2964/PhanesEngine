#pragma once

#include "Phanes/Renderer/VertexArray/VertexArray.h"

namespace Phanes
{
    class OpenGLVtxArr : public VtxArr
    {
    public:
        OpenGLVtxArr();
        ~OpenGLVtxArr() override;

        void Bind() const override;
        void Unbind() const override;

        void AddVtxBuffer(const Ref<VtxBuffer>& buffer) override;
        void SetIdxBuffer(const Ref<IdxBuffer>& buffer) override;

        pn_forceinline const std::vector<Ref<VtxBuffer>>& GetVtxBuffers() const override { return vtx_buffers; }
        pn_forceinline const Ref<IdxBuffer>& GetIdxBuffer() const override { return idx_buffer; }
    private:
        uint32_t vtx_arr_id = 0;

        std::vector<Ref<VtxBuffer>> vtx_buffers;
        Ref<IdxBuffer> idx_buffer;
    };
}

