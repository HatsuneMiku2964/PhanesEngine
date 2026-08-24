#pragma once

namespace PN
{
    class Transform
    {
    public:
        Transform(const glm::vec2& scale = {1.f, 1.f}, float rotation = 0.f, const glm::vec3& position = {0.f, 0.f, 0.f});
        Transform(const glm::vec3& scale, float rotation, const glm::vec3& position);

        void SetScale(const glm::vec2& scale) { SetScale({scale.x, scale.y, 1.0f}); }
        void SetScale(const glm::vec3& scale) { m_scale = scale; m_dirty = true; }
        const glm::vec3& GetScale() const { return m_scale; }

        void SetRotation(float degree) { m_rot_deg = degree; m_dirty = true; }
        float GetRotation() const { return m_rot_deg; }

        void SetPosition(const glm::vec2& pos) { SetPosition({pos.x, pos.y, 0.0f}); }
        void SetPosition(const glm::vec3& pos) { m_pos = pos; m_dirty = true; }
        const glm::vec3& GetPosition() const { return m_pos; }

        const glm::mat4& GetTransformMat() const;

    private:
        glm::vec3 m_pos;
        glm::vec3 m_scale;
        float m_rot_deg;

        mutable bool m_dirty = true;
        mutable glm::mat4 m_cached_transform{1.0f};
    };
}