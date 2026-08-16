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
        glm::vec2 TexCoord;
        float TexIdx;
    };
    struct Renderer2D_Data
    {
        static constexpr int MAX_QUADS_CNT = 10000;
        static constexpr int MAX_VERTICES = MAX_QUADS_CNT * 4;
        static constexpr int MAX_INDICES = MAX_QUADS_CNT * 6;
        static constexpr int MAX_TEX_SLOT_CNT = 32;

        Ref<VtxArr> VAO;
        Ref<VtxBuffer> VBO;
        Ref<Shader> TexShader;
        Ref<Texture2D> WhiteTex;

        uint32_t IdxCnt = 0;

        Quad_vtx* BufferStart = nullptr;
        Quad_vtx* BufferPtr = nullptr;

        std::array<Ref<Texture2D>, MAX_TEX_SLOT_CNT> Textures;
        uint32_t TexSlotIdx = 1; // 0 is the white yex
    };
    static Renderer2D_Data* data;


    void Renderer2D::Init()
    {
        PROFILE_FN();

        data = new Renderer2D_Data();
        data->VAO = VtxArr::Create();

        BufferLayout layout = {
            ShaderDataType::Float2,
            ShaderDataType::Float4,
            ShaderDataType::Float2,
            ShaderDataType::Float,
        };
        data->VBO = VtxBuffer::Create(Renderer2D_Data::MAX_VERTICES * sizeof(Quad_vtx));
        data->VBO->ConfigLayout(layout);
        data->VAO->AddVtxBuffer(data->VBO);

        data->BufferStart = new Quad_vtx[Renderer2D_Data::MAX_VERTICES];

        uint32_t* indices = new uint32_t[Renderer2D_Data::MAX_INDICES];
        uint32_t offset = 0;
        for (uint32_t i = 0; i < Renderer2D_Data::MAX_INDICES; i += 6) {
            indices[i + 0] = offset + 0;
            indices[i + 1] = offset + 1;
            indices[i + 2] = offset + 2;

            indices[i + 3] = offset + 2;
            indices[i + 4] = offset + 3;
            indices[i + 5] = offset + 0;

            offset += 4;
        }

        Ref<IdxBuffer> ibo = IdxBuffer::Create(indices, Renderer2D_Data::MAX_INDICES);
        data->VAO->SetIdxBuffer(ibo);
        delete[] indices;

        data->WhiteTex = Texture2D::Create(1, 1);
        static constexpr uint32_t white_tex_data = 0xffffffff;
        data->WhiteTex->SetData(&white_tex_data, sizeof(uint32_t));

        int samplers[Renderer2D_Data::MAX_TEX_SLOT_CNT];
        for (uint32_t i = 0; i < Renderer2D_Data::MAX_TEX_SLOT_CNT; ++i) samplers[i] = i;
        
        data->TexShader = Shader::Create("../Game/Assets/Shaders/Texture.shader");
        data->TexShader->Bind();
        data->TexShader->SetUniform("u_tex", (int*) samplers, Renderer2D_Data::MAX_TEX_SLOT_CNT);

        data->Textures[0] = data->WhiteTex;

        data->VAO->Unbind();
    }
    void Renderer2D::Shutdown() { PROFILE_FN(); delete data; }

    void Renderer2D::BeginScene(const OrthographicCamera& camera)
    {
        data->TexShader->Bind();
        data->TexShader->SetUniform("u_view_proj", camera.GetVPMat());
        data->WhiteTex->Bind();

        data->BufferPtr = data->BufferStart;
        data->IdxCnt = 0;

        data->TexSlotIdx = 1;
    }
    void Renderer2D::EndScene()
    {
        PROFILE_FN();

        uint32_t data_size = static_cast<uint32_t>((uint8_t*) data->BufferPtr - (uint8_t*) data->BufferStart);
        data->VBO->SetData(data->BufferStart, data_size);

        Flush();
    }

    void Renderer2D::Flush()
    {
        for (uint32_t i = 0; i < data->TexSlotIdx; ++i) data->Textures[i]->Bind(i);
        RenderCmd::DrawIndexed(data->VAO, data->IdxCnt);
    }

    void Renderer2D::DrawQuad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color)
    {
        DrawQuad({pos.x, pos.y, 0.f}, size, color);
    }
    void Renderer2D::DrawQuad(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color)
    {
        {
            data->BufferPtr->Pos = pos;
            data->BufferPtr->Color = color;
            data->BufferPtr->TexCoord = {0.f, 0.f,};
            data->BufferPtr->TexIdx = 0.f;
            data->BufferPtr++;

            data->BufferPtr->Pos = {pos.x + size.x, pos.y};
            data->BufferPtr->Color = color;
            data->BufferPtr->TexCoord = {1.f, 0.f,};
            data->BufferPtr->TexIdx = 0.f;
            data->BufferPtr++;

            data->BufferPtr->Pos = {pos.x + size.x, pos.y + size.y};
            data->BufferPtr->Color = color;
            data->BufferPtr->TexCoord = {1.f, 1.f,};
            data->BufferPtr->TexIdx = 0.f;
            data->BufferPtr++;

            data->BufferPtr->Pos = {pos.x, pos.y + size.y};
            data->BufferPtr->Color = color;
            data->BufferPtr->TexCoord = {0.f, 1.f,};
            data->BufferPtr->TexIdx = 0.f;
            data->BufferPtr++;
        }
        data->IdxCnt += 6;
    }
    void Renderer2D::DrawQuad(const glm::vec2& pos, const glm::vec2& size, const Ref<Texture2D>& texture, float tile_factor)
    {
        DrawQuad({pos.x, pos.y, 0.f}, size, texture, tile_factor);
    }
    void Renderer2D::DrawQuad(const glm::vec3& pos, const glm::vec2& size, const Ref<Texture2D>& texture, float tile_factor)
    {
        static constexpr glm::vec4 color = {1.f, 1.f, 1.f, 1.f};

        float texture_idx = 0.f;
        for (uint32_t i = 1; i < data->TexSlotIdx; ++i) {
            if (data->Textures[i]->GetTexId() == texture->GetTexId()) {
                texture_idx = (float) i; break;
            }
        }
        if (texture_idx == 0.f)
        {
            if (data->TexSlotIdx >= Renderer2D_Data::MAX_TEX_SLOT_CNT)
            {
                EndScene();
                data->BufferPtr = data->BufferStart;
                data->IdxCnt = 0;
                data->TexSlotIdx = 1;
            }
            texture_idx = (float) data->TexSlotIdx;
            data->Textures[data->TexSlotIdx] = texture;
            data->TexSlotIdx++;
        }

        {
            data->BufferPtr->Pos = pos;
            data->BufferPtr->Color = color;
            data->BufferPtr->TexCoord = {0.f, 0.f};
            data->BufferPtr->TexIdx = texture_idx;
            data->BufferPtr++;

            data->BufferPtr->Pos = {pos.x + size.x, pos.y};
            data->BufferPtr->Color = color;
            data->BufferPtr->TexCoord = {tile_factor, 0.f};
            data->BufferPtr->TexIdx = texture_idx;
            data->BufferPtr++;

            data->BufferPtr->Pos = {pos.x + size.x, pos.y + size.y};
            data->BufferPtr->Color = color;
            data->BufferPtr->TexCoord = {tile_factor, tile_factor};
            data->BufferPtr->TexIdx = texture_idx;
            data->BufferPtr++;

            data->BufferPtr->Pos = {pos.x, pos.y + size.y};
            data->BufferPtr->Color = color;
            data->BufferPtr->TexCoord = {0.f, tile_factor};
            data->BufferPtr->TexIdx = texture_idx;
            data->BufferPtr++;
        }
        data->IdxCnt += 6;
    }
}
