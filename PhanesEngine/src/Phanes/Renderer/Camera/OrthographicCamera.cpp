#include "pnpch.h"
#include "OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Phanes
{
    OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
        : view_mat(1.f), proj_mat(glm::ortho(left, right, bottom, top, -1.f, 1.f))
    {
        vp_mat = proj_mat * view_mat;
    }

    void OrthographicCamera::UpdateViewMat()
    {
        glm::mat4 transform = glm::translate(glm::mat4(1.f), pos) *
                              glm::rotate(glm::mat4(1.f), glm::radians(rot), glm::vec3(0, 0, 1));
        view_mat = glm::inverse(transform);
        vp_mat = proj_mat * view_mat;
    }
}
