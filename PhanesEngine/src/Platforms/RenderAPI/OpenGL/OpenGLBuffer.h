#pragma once

#include <span>

#include "Phanes/Renderer/Buffer/Buffer.h"

namespace Phanes
{
    class OpenGLVtxBuffer : public VtxBuffer
    {
    public:
        OpenGLVtxBuffer(std::span<const float> span);
        OpenGLVtxBuffer(std::span<const float> span, const BufferLayout& layout);
        ~OpenGLVtxBuffer() override;

        void Bind() const override;
        void Unbind() const override;

        void ConfigLayout(const BufferLayout &layout) override;

        pn_forceinline const BufferLayout& GetLayout() const override { return layout; }
        pn_forceinline uint32_t GetCount() const override { return elem_cnt; }

    private:
        void init(const std::span<const float>& span_);

    private:
        BufferLayout layout = {};
        uint32_t buffer_id = 0;
        uint32_t elem_cnt = 0;
    };
}


namespace Phanes
{
    class OpenGLIdxBuffer : public IdxBuffer
    {
    public:
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
