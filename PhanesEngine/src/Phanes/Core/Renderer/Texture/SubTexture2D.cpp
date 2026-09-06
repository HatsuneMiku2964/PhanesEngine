#include "pnpch.h"
#include "SubTexture2D.h"

#include "Platforms/RenderAPI/OpenGL/OpenGLSubTexture2D.h"

namespace PN
{
    Ref<SubTexture2D> SubTexture2D::Create(const Texture2D& texture, const SubTextureComp& data)
    {
        switch (Renderer::GetAPI()) {
        case RenderAPI::RendererAPI::OpenGL:       return CreateRef<OpenGLSubTexture2D>(texture, &data);
        case RenderAPI::RendererAPI::None:         PN_CORE_ASSERT(false, "Renderer API should not be None!!"); return nullptr;
        default:                                   PN_CORE_ASSERT(false, "Unknown renderer API"); return nullptr;
        }
    }
}
