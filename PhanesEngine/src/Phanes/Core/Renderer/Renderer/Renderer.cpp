#include "pnpch.h"
#include "Renderer.h"

#include "Phanes/Core/Renderer/RenderCommand/RenderCommand.h"
#include "Platforms/RenderAPI/OpenGL/OpenGLShader.h"

namespace PN
{
    Renderer::SceneData* Renderer::scene_data = new SceneData();

    void Renderer::Init() {
        RenderCmd::Init();
    }

    void Renderer::BeginScene(OrthographicCamera& camera) { scene_data->vp_mat = camera.GetVPMat(); }
    void Renderer::EndScene() {}

    void Renderer::Submit(const Ref<Shader>& shader, const Ref<VtxArr>& vao, const glm::mat4& transform)
    {
        shader->Bind();

        // TODO: these 2 lines sucks
        std::dynamic_pointer_cast<OpenGLShader>(shader)->SetUniform("u_view_proj", scene_data->vp_mat);
        std::dynamic_pointer_cast<OpenGLShader>(shader)->SetUniform("u_model", transform);

        vao->Bind();
        RenderCmd::DrawIndexed(vao);
    }
}
