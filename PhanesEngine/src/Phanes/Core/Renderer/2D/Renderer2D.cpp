#include "pnpch.h"
#include "Renderer2D.h"

#include <glm/ext/matrix_transform.hpp>

#include "Phanes/Core/Renderer/RenderCommand/RenderCommand.h"
#include "Phanes/Core/Renderer/Texture/Texture.h"

namespace PN
{
    struct Renderer2DData
    {
        Ref<VtxArr> vao;
        Ref<Shader> tex_shader;
        Ref<Texture2D> white_tex;
    };
    static Renderer2DData* data;


    void Renderer2D::Init()
    {
        PROFILE_FN();

        data = new Renderer2DData();
        data->vao = VtxArr::Create();

        constexpr float vertices[] = {
            -0.5f, -0.5f, 0.f, 0.f,
             0.5f, -0.5f, 1.f, 0.f,
             0.5f,  0.5f, 1.f, 1.f,
            -0.5f,  0.5f, 0.f, 1.f
        };
        Ref<VtxBuffer> vbo;
        BufferLayout layout = {ShaderDataType::Float2, ShaderDataType::Float2};
        vbo = VtxBuffer::Create(vertices, layout);

        uint32_t indices[] = {0, 1, 2, 2, 3, 0};
        Ref<IdxBuffer> ibo;
        ibo = IdxBuffer::Create(indices);

        data->tex_shader = Shader::Create("../Game/Assets/Shaders/Texture.shader");
        data->tex_shader->Bind();
        data->tex_shader->SetUniform("u_tex", 0);

        data->white_tex = Texture2D::Create(1, 1);
        static constinit uint32_t white_tex_data = 0xffffffff;
        data->white_tex->SetData(&white_tex_data, sizeof(uint32_t));

        data->vao->AddVtxBuffer(vbo);
        data->vao->SetIdxBuffer(ibo);
        data->vao->Unbind();
    }
    void Renderer2D::Shutdown() { PROFILE_FN(); delete data; }

    void Renderer2D::BeginScene(const OrthographicCamera& camera)
    {
        data->tex_shader->Bind();
        data->tex_shader->SetUniform("u_view_proj", camera.GetVPMat());
    }
    void Renderer2D::EndScene() {}

    void Renderer2D::DrawQuad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color)
    {
        DrawQuad({pos.x, pos.y, 0.f}, size, color);
    }
    void Renderer2D::DrawQuad(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color)
    {
        data->tex_shader->SetUniform("u_color", color);
        data->white_tex->Bind();

        glm::mat4 model = glm::translate(glm::mat4(1.f), pos) * glm::scale(glm::mat4(1.f), {size, 1.f});
        data->tex_shader->SetUniform("u_model", model);

        data->vao->Bind();
        RenderCmd::DrawIndexed(data->vao);
    }
    void Renderer2D::DrawQuad(const glm::vec2& pos, const glm::vec2& size, const Ref<Texture2D>& texture, float tile_factor)
    {
        DrawQuad({pos.x, pos.y, 0.f}, size, texture);
    }
    void Renderer2D::DrawQuad(const glm::vec3& pos, const glm::vec2& size, const Ref<Texture2D>& texture, float tile_factor)
    {
        data->tex_shader->SetUniform("u_color", glm::vec4(1.f));
        data->tex_shader->SetUniform("u_tile", tile_factor);
        texture->Bind();

        glm::mat4 model = glm::translate(glm::mat4(1.f), pos) * glm::scale(glm::mat4(1.f), {size, 1.f});
        data->tex_shader->SetUniform("u_model", model);

        data->vao->Bind();
        RenderCmd::DrawIndexed(data->vao);
    }
}
