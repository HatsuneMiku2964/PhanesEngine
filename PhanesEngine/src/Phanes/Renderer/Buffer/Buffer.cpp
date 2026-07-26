#include "pnpch.h"
#include "Buffer.h"

#include <imgui.h>

#include "Phanes/Renderer/Renderer/Renderer.h"
#include "Platforms/RenderAPI/OpenGL/OpenGLBuffer.h"

namespace Phanes
{
    VtxBuffer* VtxBuffer::Create(std::span<const float> vertices)
    {
        switch (Renderer::GetAPI()) {
        case RendererAPI::OpenGL:       return new OpenGLVtxBuffer(vertices);
        case RendererAPI::None:         PN_CORE_ASSERT(false, "Renderer API should not be None!!"); return nullptr;
        default:                        PN_CORE_ASSERT(false, "Unknown renderer API"); return nullptr;
        }
    }
    VtxBuffer* VtxBuffer::Create(std::span<const float> vertices, const BufferLayout& layout)
    {
        switch (Renderer::GetAPI()) {
        case RendererAPI::OpenGL:       return new OpenGLVtxBuffer(vertices, layout);
        case RendererAPI::None:         PN_CORE_ASSERT(false, "Renderer API should not be None!!"); return nullptr;
        default:                        PN_CORE_ASSERT(false, "Unknown renderer API"); return nullptr;
        }
    }

    IdxBuffer* IdxBuffer::Create(std::span<const uint32_t> indices)
    {
        switch (Renderer::GetAPI()) {
        case RendererAPI::OpenGL:       return new OpenGLIdxBuffer(indices);
        case RendererAPI::None:         PN_CORE_ASSERT(false, "Renderer API should not be None!!"); return nullptr;
        default:                        PN_CORE_ASSERT(false, "Unknown renderer API"); return nullptr;
        }
    }
}
