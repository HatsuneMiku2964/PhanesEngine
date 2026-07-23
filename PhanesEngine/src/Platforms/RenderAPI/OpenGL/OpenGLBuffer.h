#pragma once

#include "Phanes/Renderer/Buffer/Buffer.h"

namespace Phanes
{
    class OpenGLVtxBuffer : public VtxBuffer
    {
    public:
        OpenGLVtxBuffer(float* vertices, unsigned int cnt);
        virtual ~OpenGLVtxBuffer() override;

        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual inline unsigned int GetCount() const override { return elem_cnt; }

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
        virtual ~OpenGLIdxBuffer() override;

        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual inline unsigned int GetCount() const override { return elem_cnt; }

    private:
        unsigned int buffer_id = 0;
        unsigned int elem_cnt = 0;
    };
}
