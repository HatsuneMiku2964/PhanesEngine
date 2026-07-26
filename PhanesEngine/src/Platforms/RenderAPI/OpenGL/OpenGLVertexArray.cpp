#include "pnpch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Phanes
{
    OpenGLVtxArr::OpenGLVtxArr() { glCreateVertexArrays(1, &vtx_arr_id); }
    OpenGLVtxArr::~OpenGLVtxArr() { glDeleteVertexArrays(1, &vtx_arr_id); }

    void OpenGLVtxArr::Bind() const { glBindVertexArray(vtx_arr_id); }
    void OpenGLVtxArr::Unbind() const { glBindVertexArray(0); }

    void OpenGLVtxArr::AddVtxBuffer(const std::shared_ptr<VtxBuffer>& buffer)
    {
        PN_ASSERT(buffer->GetLayout().size(), "Vertex buffer has no layouts!!");

        glBindVertexArray(vtx_arr_id);
        buffer->Bind();

        buffer->ConfigLayout(buffer->GetLayout());

        vtx_buffers.push_back(buffer);
    }
    void OpenGLVtxArr::SetIdxBuffer(const std::shared_ptr<IdxBuffer>& buffer)
    {
        glBindVertexArray(vtx_arr_id);
        buffer->Bind();

        idx_buffer = buffer;
    }
}
