#pragma once

#include "Phanes/Renderer/Buffer/Buffer.h"

namespace Phanes
{
    class OpenGLVtxBuffer : public VtxBuffer
    {
    public:
        OpenGLVtxBuffer(float* vertices, unsigned int cnt);
        ~OpenGLVtxBuffer() override;

        void Bind() const override;
        void Unbind() const override;

        pn_forceinline unsigned int GetCount() const override { return elem_cnt; }

    private:
        unsigned int buffer_id = 0;
        unsigned int elem_cnt = 0;
    };
}


namespace Phanes
{
    class OpenGLIdxBuffer : public IdxBuffer
    {
    public:
        OpenGLIdxBuffer(unsigned int* indices, unsigned int cnt);
        ~OpenGLIdxBuffer() override;

        void Bind() const override;
        void Unbind() const override;

        pn_forceinline unsigned int GetCount() const override { return elem_cnt; }

    private:
        unsigned int buffer_id = 0;
        unsigned int elem_cnt = 0;
    };
}
