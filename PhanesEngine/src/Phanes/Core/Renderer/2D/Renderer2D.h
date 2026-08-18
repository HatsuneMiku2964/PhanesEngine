#pragma once


namespace PN
{
    class Texture2D;

    class Renderer2D
    {
    public:
        static void Init();
        static void Shutdown();

        static void BeginScene(const OrthographicCamera& camera);
        static void EndScene();
        static void Flush();

        static void DrawQuad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color);
        static void DrawQuad(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color);

        static void DrawQuad(const Transform& transform, const glm::vec4& color);

        static void DrawQuad(const glm::vec3& pos, const glm::vec2& size, const Ref<Texture2D>& texture, float tile_factor = 1.f);
        static void DrawQuad(const glm::vec2& pos, const glm::vec2& size, const Ref<Texture2D>& texture, float tile_factor = 1.f);
    };
}
