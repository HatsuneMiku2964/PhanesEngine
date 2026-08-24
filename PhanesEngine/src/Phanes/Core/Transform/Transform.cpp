#include "pnpch.h"
#include "Transform.h"
#include <glm/ext/matrix_transform.hpp>

namespace PN
{
    Transform::Transform(const glm::vec2& scale, float rotation, const glm::vec3& position)
        : m_pos(position), m_scale(scale, 1.0f), m_rot_deg(rotation)
    {
    }

    Transform::Transform(const glm::vec3& scale, float rotation, const glm::vec3& position)
        : m_pos(position), m_scale(scale), m_rot_deg(rotation)
    {
    }

    const glm::mat4& Transform::GetTransformMat() const
    {
        if (m_dirty)
        {
            glm::mat4 translationMat = glm::translate(glm::mat4(1.0f), m_pos);
            glm::mat4 rotationMat = glm::rotate(glm::mat4(1.0f), glm::radians(m_rot_deg), glm::vec3(0.0f, 0.0f, 1.0f));
            glm::mat4 scaleMat = glm::scale(glm::mat4(1.0f), m_scale);

            m_cached_transform = translationMat * rotationMat * scaleMat;
            m_dirty = false;
        }
        return m_cached_transform;
    }

}