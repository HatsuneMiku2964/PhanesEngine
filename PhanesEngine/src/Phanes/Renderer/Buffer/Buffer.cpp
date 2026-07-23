#include "pnpch.h"
#include "Buffer.h"

#include <imgui.h>

#include "Phanes/Renderer/Renderer/Renderer.h"
#include "Platforms/RenderAPI/OpenGL/OpenGLBuffer.h"

namespace Phanes
{
    VtxBuffer* VtxBuffer::Create(float* vertices, unsigned int size)
    {
        switch (Renderer::GetAPI()) {
        case RendererAPI::OpenGL:       return new OpenGLVtxBuffer(vertices, size);
        case RendererAPI::None:         PN_CORE_LOG_ERROR("Renderer API should not be None!!"); return nullptr;
        default:                        PN_CORE_LOG_ERROR("Unknown renderer API"); return nullptr;
        }
    }
    IdxBuffer* IdxBuffer::Create(unsigned int* indices, unsigned int size)
    {
        switch (Renderer::GetAPI()) {
        case RendererAPI::OpenGL:       return new OpenGLIdxBuffer(indices, size);
        case RendererAPI::None:         PN_CORE_LOG_ERROR("Renderer API should not be None!!"); return nullptr;
        default:                        PN_CORE_LOG_ERROR("Unknown renderer API"); return nullptr;
        }
    }
}
