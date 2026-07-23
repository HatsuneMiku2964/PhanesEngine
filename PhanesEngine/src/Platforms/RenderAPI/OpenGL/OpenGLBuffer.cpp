#include "pnpch.h"
#include "OpenGLBuffer.h"

#include <glad/glad.h>

namespace Phanes
{
    OpenGLVtxBuffer::OpenGLVtxBuffer(float* vertices, unsigned int cnt)
        : elem_cnt(cnt)
    {
        glCreateBuffers(1, &this->buffer_id);
        glBindBuffer(GL_ARRAY_BUFFER, this->buffer_id);
        glBufferData(GL_ARRAY_BUFFER, cnt * sizeof(float), (const void*) vertices, GL_STATIC_DRAW);
    }
    OpenGLVtxBuffer::~OpenGLVtxBuffer() { glDeleteBuffers(1, &this->buffer_id); }

    void OpenGLVtxBuffer::Bind() const { glBindBuffer(GL_ARRAY_BUFFER, this->buffer_id); }
    void OpenGLVtxBuffer::Unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }
}


namespace Phanes
{
    OpenGLIdxBuffer::OpenGLIdxBuffer(unsigned int* indices, unsigned int cnt)
        : elem_cnt(cnt)
    {
        glCreateBuffers(1, &this->buffer_id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->buffer_id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, cnt * sizeof(unsigned int), (const void*) indices, GL_STATIC_DRAW);
    }
    OpenGLIdxBuffer::~OpenGLIdxBuffer() { glDeleteBuffers(1, &this->buffer_id); }

    void OpenGLIdxBuffer::Bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->buffer_id); }
    void OpenGLIdxBuffer::Unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }
}
