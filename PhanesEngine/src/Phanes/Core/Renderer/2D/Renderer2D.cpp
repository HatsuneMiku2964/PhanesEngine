#include "pnpch.h"
#include "Renderer2D.h"

#include <glm/ext/matrix_transform.hpp>

#include "Phanes/Core/Renderer/RenderCommand/RenderCommand.h"
#include "Phanes/Core/Renderer/Texture/Texture.h"

namespace PN
{
    struct Quad_vtx
    {
        glm::vec2 Pos;
        glm::vec4 Color;
        glm::vec2 Tex_Coord;
    };
    struct Renderer2D_Data
    {
        static constexpr int max_quads = 10000;
        static constexpr int max_vertices = max_quads * 4;
        static constexpr int max_indices = max_quads * 6;

        Ref<VtxArr> vao;
        Ref<VtxBuffer> vbo;
        Ref<Shader> tex_shader;
        Ref<Texture2D> white_tex;

        uint32_t IdxCnt = 0;

        Quad_vtx* buffer_base = nullptr;
        Quad_vtx* buffer_ptr = nullptr;
    };
    static Renderer2D_Data* data;


    void Renderer2D::Init()
    {
        PROFILE_FN();

        data = new Renderer2D_Data();
        data->vao = VtxArr::Create();

        BufferLayout layout = {
            ShaderDataType::Float2,
            ShaderDataType::Float4,
            ShaderDataType::Float2,
        };
        data->vbo = VtxBuffer::Create(Renderer2D_Data::max_vertices * sizeof(Quad_vtx));
        data->vbo->ConfigLayout(layout);
        data->buffer_base = new Quad_vtx[Renderer2D_Data::max_vertices];

        uint32_t* indices = new uint32_t[Renderer2D_Data::max_indices];
        uint32_t offset = 0;
        for (uint32_t i = 0; i < Renderer2D_Data::max_indices; i += 6) {
            indices[i + 0] = offset + 0;
            indices[i + 1] = offset + 1;
            indices[i + 2] = offset + 2;

            indices[i + 3] = offset + 2;
            indices[i + 4] = offset + 3;
            indices[i + 5] = offset + 0;

            offset += 4;
        }

        Ref<IdxBuffer> ibo;
        ibo = IdxBuffer::Create(indices, Renderer2D_Data::max_indices);
        delete[] indices;

        data->tex_shader = Shader::Create("../Game/Assets/Shaders/Texture.shader");
        data->tex_shader->Bind();
        //data->tex_shader->SetUniform("u_tex", 0);

        data->white_tex = Texture2D::Create(1, 1);
        static constexpr uint32_t white_tex_data = 0xffffffff;
        data->white_tex->SetData(&white_tex_data, sizeof(uint32_t));

        data->vao->AddVtxBuffer(data->vbo);
        data->vao->SetIdxBuffer(ibo);
        data->vao->Unbind();
    }
    void Renderer2D::Shutdown() { PROFILE_FN(); delete data; }

    void Renderer2D::BeginScene(const OrthographicCamera& camera)
    {
        data->tex_shader->Bind();
        data->tex_shader->SetUniform("u_view_proj", camera.GetVPMat());
        data->white_tex->Bind();

        data->buffer_ptr = data->buffer_base;
        data->IdxCnt = 0;
    }
    void Renderer2D::EndScene()
    {
        PROFILE_FN();

        uint32_t data_size = (uint8_t*) data->buffer_ptr - (uint8_t*) data->buffer_base;
        data->vbo->SetData(data->buffer_base, data_size);

        Flush();
    }
    void Renderer2D::Flush()
    {
        if (data->IdxCnt == 0) return;
        data->vao->Bind();
        RenderCmd::DrawIndexed(data->vao, data->IdxCnt);
    }

    void Renderer2D::DrawQuad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color)
    {
        DrawQuad({pos.x, pos.y, 0.f}, size, color);
    }
    void Renderer2D::DrawQuad(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color)
    {
        data->buffer_ptr->Pos = pos;
        data->buffer_ptr->Color = color;
        data->buffer_ptr->Tex_Coord = {0.f, 0.f,};
        data->buffer_ptr++;

        data->buffer_ptr->Pos = {pos.x + size.x, pos.y};
        data->buffer_ptr->Color = color;
        data->buffer_ptr->Tex_Coord = {1.f, 0.f,};
        data->buffer_ptr++;

        data->buffer_ptr->Pos = {pos.x + size.x, pos.y + size.y};
        data->buffer_ptr->Color = color;
        data->buffer_ptr->Tex_Coord = {1.f, 1.f,};
        data->buffer_ptr++;

        data->buffer_ptr->Pos = {pos.x, pos.y + size.y};
        data->buffer_ptr->Color = color;
        data->buffer_ptr->Tex_Coord = {0.f, 1.f,};
        data->buffer_ptr++;

        data->IdxCnt += 6;
    }
    void Renderer2D::DrawQuad(const glm::vec2& pos, const glm::vec2& size, const Ref<Texture2D>& texture, float tile_factor)
    {
        DrawQuad({pos.x, pos.y, 0.f}, size, texture, tile_factor);
    }
    void Renderer2D::DrawQuad(const glm::vec3& pos, const glm::vec2& size, const Ref<Texture2D>& texture, float tile_factor)
    {
        data->tex_shader->SetUniform("u_color", glm::vec4(1.f));
        data->tex_shader->SetUniform("u_tile", tile_factor);
        texture->Bind();

        glm::mat4 model = glm::translate(glm::mat4(1.f), pos) * glm::scale(glm::mat4(1.f), {size, 1.f});

        data->vao->Bind();
        RenderCmd::DrawIndexed(data->vao);
    }
}
