#include "pnpch.h"
#include "Renderer.h"

#include "Phanes/Renderer/RenderCommand/RenderCommand.h"

namespace Phanes
{
    Renderer::SceneData* Renderer::scene_data = new SceneData();

    void Renderer::BeginScene(OrthographicCamera& camera) { scene_data->vp_mat = camera.GetVPMat(); }
    void Renderer::EndScene() {}

    void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VtxArr>& vao)
    {
        shader->Bind();
        shader->SetUniformMat4("u_view_proj", scene_data->vp_mat);

        vao->Bind();
        RenderCmd::DrawIndexed(vao);
    }
}
