#include "pnpch.h"
#include "Shader.h"

#include "Phanes/Core/Renderer/Renderer/Renderer.h"
#include "Platforms/RenderAPI/OpenGL/OpenGLShader.h"

namespace PN
{
    Ref<Shader> Shader::Create(const std::string& path)
    {
        switch (Renderer::GetAPI()) {
        case RenderAPI::RendererAPI::OpenGL:       return std::make_shared<OpenGLShader>(path);
        case RenderAPI::RendererAPI::None:         PN_CORE_ASSERT(false, "Renderer API should not be None!!"); return nullptr;
        default:                                   PN_CORE_ASSERT(false, "Unknown renderer API"); return nullptr;
        }
    }

    void ShaderManager::Add(const Ref<Shader>& shader)
    {
        const std::string& name = shader->GetName();
        Add(name, shader);
    }
    void ShaderManager::Add(const std::string& name, const Ref<Shader>& shader)
    {
        PN_CORE_ASSERT(!Exists(name), "shader already exists!!");
        shaders[name] = shader;
    }

    Ref<Shader> ShaderManager::Load(const std::string& filepath)
    {
        Ref<Shader> shader = Shader::Create(filepath);
        Add(shader);
        return shader;
    }
    Ref<Shader> ShaderManager::Load(const std::string& name, const std::string& filepath)
    {
        Ref<Shader> shader = Shader::Create(filepath);
        Add(name, shader);
        return shader;
    }

    Ref<Shader> ShaderManager::Get(const std::string& name)
    {
        PN_CORE_ASSERT(Exists(name), "shader don't exists!!");
        return shaders[name];
    }
}
