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

        void AddVtxBuffer(const std::shared_ptr<VtxBuffer>& buffer) override;
        void SetIdxBuffer(const std::shared_ptr<IdxBuffer>& buffer) override;

        pn_forceinline const std::vector<std::shared_ptr<VtxBuffer>>& GetVtxBuffers() const override { return vtx_buffers; }
        pn_forceinline const std::shared_ptr<IdxBuffer>& GetIdxBuffer() const override { return idx_buffer; }
    private:
        uint32_t vtx_arr_id = 0;

        std::vector<std::shared_ptr<VtxBuffer>> vtx_buffers;
        std::shared_ptr<IdxBuffer> idx_buffer;
    };
}

