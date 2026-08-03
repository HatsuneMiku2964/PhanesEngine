#pragma once

#include <glm/glm.hpp>

namespace Phanes
{
    class OrthographicCamera
    {
    public:
        OrthographicCamera(float left, float right, float bottom, float top);

        pn_forceinline const glm::mat4& GetProjMat() const { return proj_mat; }
        pn_forceinline const glm::mat4& GetViewMat() const { return view_mat; }
        pn_forceinline const glm::mat4& GetVPMat() const { return vp_mat; }

        pn_forceinline const glm::vec3& GetPos() const { return pos; }
        pn_forceinline float GetRot() const { return rot; }
        pn_forceinline void SetPos(const glm::vec3& new_pos) { pos = new_pos; UpdateViewMat(); }
        pn_forceinline void SetRot(float new_rot) { rot = new_rot; UpdateViewMat(); }

    private:
        void UpdateViewMat();

    private:
        glm::mat4 view_mat;
        glm::mat4 proj_mat;
        glm::mat4 vp_mat;

        glm::vec3 pos = {0.f, 0.f, 0.f};
        float rot = 0.f;
    };
}

