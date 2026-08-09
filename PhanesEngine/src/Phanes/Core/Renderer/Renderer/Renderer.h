#pragma once

#include "Phanes/Core/Renderer/Shader/Shader.h"
#include "Phanes/Core/Renderer/RenderAPI.h"
#include "Phanes/Core/Renderer/Camera/OrthographicCamera.h"

namespace PN
{
    class Renderer
    {
    public:
        static void Init();
        static void OnWindowResized(uint32_t width, uint32_t height);

        static void BeginScene(const OrthographicCamera &camera);
        static void EndScene();

        static void Submit(const Ref<Shader>& shader, const Ref<VtxArr>& vao, const glm::mat4& transform = glm::mat4(1.f));

        pn_forceinline static RenderAPI::RendererAPI GetAPI() { return RenderAPI::GetAPI(); }
    private:
        struct SceneData
        {
            glm::mat4 vp_mat;
        };
        static SceneData* scene_data;
    };
}
