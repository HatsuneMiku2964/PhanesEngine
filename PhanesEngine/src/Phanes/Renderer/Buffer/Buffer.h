#pragma once

namespace Phanes
{
    class VtxBuffer
    {
    public:
        virtual ~VtxBuffer() {}

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual unsigned int GetCount() const = 0;

        static VtxBuffer* Create(float* vertices, unsigned int size);
    };

    class IdxBuffer
    {
    public:
        virtual ~IdxBuffer() {}

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual unsigned int GetCount() const = 0;

        static IdxBuffer* Create(unsigned int* indices, unsigned int size);
    };
}
