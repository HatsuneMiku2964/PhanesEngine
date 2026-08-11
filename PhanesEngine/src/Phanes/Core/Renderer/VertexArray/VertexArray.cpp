#include "pnpch.h"
#include "VertexArray.h"

#include "Phanes/Core/Renderer/Renderer/Renderer.h"
#include "Platforms/RenderAPI/OpenGL/OpenGLVertexArray.h"

namespace PN
{
    Ref<VtxArr> VtxArr::Create()
    {
        switch (Renderer::GetAPI()) {
        case RenderAPI::RendererAPI::OpenGL:       return std::make_shared<OpenGLVtxArr>();
        case RenderAPI::RendererAPI::None:         PN_CORE_ASSERT(false, "Renderer API should not be None!!"); return nullptr;
        default:                        PN_CORE_ASSERT(false, "Unknown renderer API"); return nullptr;
        }
    }
}
