#include "pnpch.h"
#include "Shader.h"

#include "Phanes/Core/Renderer/Renderer/Renderer.h"
#include "Platforms/RenderAPI/OpenGL/OpenGLShader.h"

namespace PN
{
    Shader* Shader::Create(const std::string& path)
    {
        switch (Renderer::GetAPI()) {
        case RenderAPI::RendererAPI::OpenGL:       return new OpenGLShader(path);
        case RenderAPI::RendererAPI::None:         PN_CORE_ASSERT(false, "Renderer API should not be None!!"); return nullptr;
        default:                                   PN_CORE_ASSERT(false, "Unknown renderer API"); return nullptr;
        }
    }
}
