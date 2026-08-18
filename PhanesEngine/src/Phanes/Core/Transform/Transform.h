#pragma once

namespace PN
{
    class Transform
    {
    public:
        Transform(const glm::vec2& scale = {1.f, 1.f}, float rotation = 0.f, const glm::vec2& position = {0.f, 0.f});
        Transform(const glm::vec3& scale, float rotation, const glm::vec3& position);

        void SetScale(const glm::vec2& scale) { SetScale({scale.x, scale.y, 1.0f}); }
        void SetScale(const glm::vec3& scale) { m_Scale = scale; m_Dirty = true; }
        const glm::vec3& GetScale() const { return m_Scale; }

        void SetRotation(float degree) { m_RotationDegree = degree; m_Dirty = true; }
        float GetRotation() const { return m_RotationDegree; }

        void SetPosition(const glm::vec2& pos) { SetPosition({pos.x, pos.y, 0.0f}); }
        void SetPosition(const glm::vec3& pos) { m_Position = pos; m_Dirty = true; }
        const glm::vec3& GetPosition() const { return m_Position; }

        const glm::mat4& GetTransformMat() const;

    private:
        glm::vec3 m_Position{0.0f};
        glm::vec3 m_Scale{1.0f, 1.0f, 1.0f};
        float m_RotationDegree = 0.0f;

        mutable bool m_Dirty = true;
        mutable glm::mat4 m_CachedTransform{1.0f};
    };

}