#include "pnpch.h"
#include "OpenGLRenderAPI.h"

#include <glad/glad.h>

namespace PN
{
    void OpenGLRenderAPI::Init()
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void OpenGLRenderAPI::Clear() { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }
    void OpenGLRenderAPI::SetClearColor(const glm::vec4& color) { glClearColor(color.r, color.g, color.b, color.a); }

    void OpenGLRenderAPI::DrawIndexed(const Ref<VtxArr>& vao)
    {
        glDrawElements(GL_TRIANGLES, vao->GetIdxBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
    }
}
