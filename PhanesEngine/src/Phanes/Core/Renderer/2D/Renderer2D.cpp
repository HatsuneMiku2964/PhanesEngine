#include "pnpch.h"
#include "Renderer2D.h"

#include <glm/ext/matrix_transform.hpp>

#include "Phanes/Core/Renderer/RenderCommand/RenderCommand.h"
#include "Phanes/Core/Renderer/Texture/SubTexture2D.h"
#include "Phanes/Core/Renderer/Texture/Texture.h"

namespace PN
{
    struct Quad_vtx
    {
        glm::vec3 Pos;
        glm::vec4 Color;
        glm::vec2 TexCoord;
        float TexIdx;
    };
    struct Renderer2D_Data
    {
        static constexpr int MAX_QUADS_CNT = 20000;
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

        Renderer2D::Statistics Stat;
    };
    static Renderer2D_Data* data;


    void Renderer2D::Init()
    {
        PROFILE_FN();

        data = new Renderer2D_Data();
        data->VAO = VtxArr::Create();

        BufferLayout layout = {
            ShaderDataType::Float3,
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
        data->Stat.DrawCallCnt++;
    }
    void Renderer2D::new_batch()
    {
        EndScene();

        data->BufferPtr = data->BufferStart;
        data->IdxCnt = 0;
        data->TexSlotIdx = 1;
    }


    void Renderer2D::DrawQuad(const Transform& transform, const glm::vec4& color)
    {
        if (data->IdxCnt >= Renderer2D_Data::MAX_INDICES) new_batch();

        static constexpr glm::vec4 quadVertexPositions[4] = {
            { -0.5f, -0.5f, 0.0f, 1.0f },
            {  0.5f, -0.5f, 0.0f, 1.0f },
            {  0.5f,  0.5f, 0.0f, 1.0f },
            { -0.5f,  0.5f, 0.0f, 1.0f }
        };
        static constexpr glm::vec2 texCoords[4] = {
            { 0.0f, 0.0f },
            { 1.0f, 0.0f },
            { 1.0f, 1.0f },
            { 0.0f, 1.0f }
        };

        const glm::mat4& transformMat = transform.GetTransformMat();

        for (int i = 0; i < 4; ++i)
        {
            data->BufferPtr->Pos = transformMat * quadVertexPositions[i];
            data->BufferPtr->Color = color;
            data->BufferPtr->TexCoord = texCoords[i];
            data->BufferPtr->TexIdx = 0.f;
            data->BufferPtr++;
        }

        data->IdxCnt += 6;
        data->Stat.QuadCnt++;
    }
    void Renderer2D::DrawQuad(const Transform& transform, const Ref<Texture2D>& texture, float tile_factor)
    {
        if (data->IdxCnt >= Renderer2D_Data::MAX_INDICES) new_batch();

        SubTextureComp* comp = texture->GetSubTextureComp();

        static constexpr glm::vec4 color = {1.f, 1.f, 1.f, 1.f};

        float texture_idx = 0.f;
        for (uint32_t i = 1; i < data->TexSlotIdx; ++i) {
            if (data->Textures[i]->GetTexId() == texture->GetTexId()) {
                texture_idx = (float) i; break;
            }
        }
        if (texture_idx == 0.f)
        {
            if (data->TexSlotIdx >= Renderer2D_Data::MAX_TEX_SLOT_CNT) new_batch();

            texture_idx = (float) data->TexSlotIdx;
            data->Textures[data->TexSlotIdx] = texture;
            data->TexSlotIdx++;
        }


        static constexpr glm::vec4 quadVertexPositions[4] = {
            { -0.5f, -0.5f, 0.0f, 1.0f },
            {  0.5f, -0.5f, 0.0f, 1.0f },
            {  0.5f,  0.5f, 0.0f, 1.0f },
            { -0.5f,  0.5f, 0.0f, 1.0f }
        };
        static constexpr glm::vec2 texCoords[4] = {
            { 0.0f, 0.0f },
            { 1.0f, 0.0f },
            { 1.0f, 1.0f },
            { 0.0f, 1.0f },
        };
        glm::vec2 texCoords_sub[4] = {
            { comp->BlockWidth * comp->Width_idx         , comp->BlockHeight * comp->Height_idx },
            { comp->BlockWidth * (comp->Width_idx + 1)   , comp->BlockHeight * comp->Height_idx },
            { comp->BlockWidth * (comp->Width_idx + 1)   , comp->BlockHeight * (comp->Height_idx+1) },
            { comp->BlockWidth * comp->Width_idx         , comp->BlockHeight * (comp->Height_idx + 1) },
        };

        const glm::mat4& transformMat = transform.GetTransformMat();

        for (int i = 0; i < 4; ++i)
        {
            const glm::vec2& tex_coord = (comp == nullptr) ? texCoords[i] : texCoords_sub[i];
            data->BufferPtr->Pos = transformMat * quadVertexPositions[i];
            data->BufferPtr->Color = color;
            data->BufferPtr->TexCoord = texCoords[i] * tile_factor;
            data->BufferPtr->TexIdx = texture_idx;
            data->BufferPtr++;
        }

        data->IdxCnt += 6;
        data->Stat.QuadCnt++;
    }

    void Renderer2D::ResetStat() { memset(&data->Stat, 0, sizeof(Statistics)); }
    const Renderer2D::Statistics& Renderer2D::GetStats() { return data->Stat; }
}
