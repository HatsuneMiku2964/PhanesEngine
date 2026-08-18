#include "pnpch.h"
#include "Transform.h"
#include <glm/ext/matrix_transform.hpp>

namespace PN
{
    Transform::Transform(const glm::vec2& scale, float rotation, const glm::vec2& position)
        : m_Position(position, 0.0f), m_Scale(scale, 1.0f), m_RotationDegree(rotation)
    {
    }

    Transform::Transform(const glm::vec3& scale, float rotation, const glm::vec3& position)
        : m_Position(position), m_Scale(scale), m_RotationDegree(rotation)
    {
    }

    const glm::mat4& Transform::GetTransformMat() const
    {
        if (m_Dirty)
        {
            glm::mat4 translationMat = glm::translate(glm::mat4(1.0f), m_Position);
            glm::mat4 rotationMat = glm::rotate(glm::mat4(1.0f), glm::radians(m_RotationDegree), glm::vec3(0.0f, 0.0f, 1.0f));
            glm::mat4 scaleMat = glm::scale(glm::mat4(1.0f), m_Scale);

            m_CachedTransform = translationMat * rotationMat * scaleMat;
            m_Dirty = false;
        }
        return m_CachedTransform;
    }

}