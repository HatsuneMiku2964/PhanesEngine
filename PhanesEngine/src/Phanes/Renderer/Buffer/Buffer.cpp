#include "pnpch.h"
#include "Buffer.h"

#include <imgui.h>

#include "Phanes/Renderer/Renderer/Renderer.h"
#include "Phanes/Renderer/RenderAPI/RenderAPI.h"
#include "Platforms/RenderAPI/OpenGL/OpenGLBuffer.h"

namespace Phanes
{
    VtxBuffer* VtxBuffer::Create(std::span<const float> vertices)
    {
        switch (Renderer::GetAPI()) {
        case RenderAPI::RendererAPI::OpenGL:       return new OpenGLVtxBuffer(vertices);
        case RenderAPI::RendererAPI::None:         PN_CORE_ASSERT(false, "Renderer API should not be None!!"); return nullptr;
        default:                        PN_CORE_ASSERT(false, "Unknown renderer API"); return nullptr;
        }
    }
    VtxBuffer* VtxBuffer::Create(std::span<const float> vertices, const BufferLayout& layout)
    {
        switch (Renderer::GetAPI()) {
        case RenderAPI::RendererAPI::OpenGL:       return new OpenGLVtxBuffer(vertices, layout);
        case RenderAPI::RendererAPI::None:         PN_CORE_ASSERT(false, "Renderer API should not be None!!"); return nullptr;
        default:                        PN_CORE_ASSERT(false, "Unknown renderer API"); return nullptr;
        }
    }

    IdxBuffer* IdxBuffer::Create(std::span<const uint32_t> indices)
    {
        switch (Renderer::GetAPI()) {
        case RenderAPI::RendererAPI::OpenGL:       return new OpenGLIdxBuffer(indices);
        case RenderAPI::RendererAPI::None:         PN_CORE_ASSERT(false, "Renderer API should not be None!!"); return nullptr;
        default:                        PN_CORE_ASSERT(false, "Unknown renderer API"); return nullptr;
        }
    }
}
