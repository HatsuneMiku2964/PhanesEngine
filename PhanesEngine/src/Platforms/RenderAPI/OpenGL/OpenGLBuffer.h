#pragma once

#include <span>

#include "Phanes/Core/Renderer/Buffer/Buffer.h"

namespace PN
{
    class OpenGLVtxBuffer : public VtxBuffer
    {
    public:
        OpenGLVtxBuffer(uint32_t size);
        OpenGLVtxBuffer(std::span<const float> span);
        OpenGLVtxBuffer(std::span<const float> span, const BufferLayout& layout);
        ~OpenGLVtxBuffer() override;

        void Bind() const override;
        void Unbind() const override;

        void ConfigLayout(const BufferLayout& layout) override;

        pn_forceinline const BufferLayout& GetLayout() const override { return layout; }
        pn_forceinline uint32_t GetCount() const override { return elem_cnt; }

        void SetData(const void* data, uint32_t size) override;

    private:
        void init(const std::span<const float>& span_);

    private:
        BufferLayout layout = {};
        uint32_t buffer_id = 0;
        uint32_t elem_cnt = 0;
    };
}


namespace PN
{
    class OpenGLIdxBuffer : public IdxBuffer
    {
    public:
        OpenGLIdxBuffer(uint32_t* indices, uint32_t cnt);
        OpenGLIdxBuffer(std::span<const uint32_t> span);
        ~OpenGLIdxBuffer() override;

        void Bind() const override;
        void Unbind() const override;

        pn_forceinline uint32_t GetCount() const override { return elem_cnt; }

    private:
        uint32_t buffer_id = 0;
        uint32_t elem_cnt = 0;
    };
}
