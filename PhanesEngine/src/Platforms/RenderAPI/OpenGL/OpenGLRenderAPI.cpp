#include "pnpch.h"
#include "OpenGLRenderAPI.h"

#include <glad/glad.h>

namespace Phanes
{
    void OpenGLRenderAPI::Clear() { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }
    void OpenGLRenderAPI::SetClearColor(const glm::vec4& color) { glClearColor(color.r, color.g, color.b, color.a); }

    void OpenGLRenderAPI::DrawIndexed(const Ref<VtxArr>& vao) {
        glDrawElements(GL_TRIANGLES, vao->GetIdxBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
    }
}
