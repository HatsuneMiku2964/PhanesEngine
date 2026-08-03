#pragma once

#include "Phanes/Renderer/Shader/Shader.h"
#include "Phanes/Renderer/RenderAPI/RenderAPI.h"
#include "Phanes/Renderer/Camera/OrthographicCamera.h"

namespace Phanes
{
    class Renderer
    {
    public:
        static void BeginScene(OrthographicCamera& camera);
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
