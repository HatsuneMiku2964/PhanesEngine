#pragma once

#include "Phanes/Renderer/Buffer/Buffer.h"

namespace Phanes
{
    class VtxArr
    {
    public:
        virtual ~VtxArr() {}

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void AddVtxBuffer(const std::shared_ptr<VtxBuffer>& buffer) = 0;
        virtual void SetIdxBuffer(const std::shared_ptr<IdxBuffer>& buffer) = 0;

        virtual const std::vector<std::shared_ptr<VtxBuffer>>& GetVtxBuffers() const = 0;
        virtual const std::shared_ptr<IdxBuffer>& GetIdxBuffer() const = 0;

        static VtxArr* Create();
    };

}
