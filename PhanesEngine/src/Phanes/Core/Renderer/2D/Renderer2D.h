#pragma once

namespace PN
{
    class Texture2D;
    class SubTexture2D;

    class Renderer2D
    {
    public:
        static void Init();
        static void Shutdown();

        static void BeginScene(const OrthographicCamera& camera);
        static void EndScene();
        static void Flush();

        static void DrawQuad(const Transform& transform, const glm::vec4& color);
        static void DrawQuad(const Transform& transform, const Ref<Texture2D>& texture, float tile_factor);

        struct Statistics
        {
            uint32_t DrawCallCnt = 0;
            uint32_t QuadCnt = 0;

            uint32_t GetVtxCnt() const { return QuadCnt * 4; }
            uint32_t GetIdxCnt() const { return QuadCnt * 6; }
        };
        static void ResetStat();
        static const Statistics& GetStats();

    private:
        static void new_batch();
    };
}
