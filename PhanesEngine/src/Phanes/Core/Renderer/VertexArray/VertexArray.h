#pragma once

#include "Phanes/Core/Renderer/Buffer/Buffer.h"

namespace PN
{
    class VtxArr
    {
    public:
        virtual ~VtxArr() {}

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void AddVtxBuffer(const Ref<VtxBuffer>& buffer) = 0;
        virtual void SetIdxBuffer(const Ref<IdxBuffer>& buffer) = 0;

        virtual const std::vector<Ref<VtxBuffer>>& GetVtxBuffers() const = 0;
        virtual const Ref<IdxBuffer>& GetIdxBuffer() const = 0;

        static Ref<VtxArr> Create();
    };

}
