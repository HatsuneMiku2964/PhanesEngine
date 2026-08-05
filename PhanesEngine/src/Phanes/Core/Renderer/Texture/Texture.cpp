#include "pnpch.h"
#include "Texture.h"

#include "Phanes/Core/Renderer/Renderer/Renderer.h"
#include "Platforms/RenderAPI/OpenGL/OpenGLTexture.h"

namespace PN
{
    Ref<Texture2D> Texture2D::Create(const std::string& path) {
        switch (Renderer::GetAPI()) {
        case RenderAPI::RendererAPI::OpenGL:       return std::make_shared<OpenGLTexture2D>(path);
        case RenderAPI::RendererAPI::None:         PN_CORE_ASSERT(false, "Renderer API should not be None!!"); return nullptr;
        default:                                   PN_CORE_ASSERT(false, "Unknown renderer API"); return nullptr;
        }
    }
}
