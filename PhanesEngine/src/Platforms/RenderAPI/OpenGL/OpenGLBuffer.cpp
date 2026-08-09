#include "pnpch.h"
#include "OpenGLBuffer.h"

#include <glad/glad.h>

// INFO: belongs to OpenGLVtxBuffer
namespace PN
{
    // TODO: remove it in the future
    pn_forceinline static GLenum ShaderDataTypeToGLenum(const ShaderData::ShaderDataType& type)
    {
        switch (type) {
        case ShaderData::ShaderDataType::Float:     return GL_FLOAT;
        case ShaderData::ShaderDataType::Float2:    return GL_FLOAT;
        case ShaderData::ShaderDataType::Float3:    return GL_FLOAT;
        case ShaderData::ShaderDataType::Float4:    return GL_FLOAT;
        case ShaderData::ShaderDataType::Mat3:      return GL_FLOAT;
        case ShaderData::ShaderDataType::Mat4:      return GL_FLOAT;
        case ShaderData::ShaderDataType::Int:       return GL_INT;
        case ShaderData::ShaderDataType::Int2:      return GL_INT;
        case ShaderData::ShaderDataType::Int3:      return GL_INT;
        case ShaderData::ShaderDataType::Int4:      return GL_INT;
        case ShaderData::ShaderDataType::None:      PN_CORE_LOG_ERROR("Invalid shader data type of \"None\"");  return 0;
        default:                                    PN_CORE_LOG_ERROR("Unknown shader data type!!");            return 0;
        }
    }

    OpenGLVtxBuffer::OpenGLVtxBuffer(std::span<const float> span) { init(span); }
    OpenGLVtxBuffer::OpenGLVtxBuffer(std::span<const float> span, const BufferLayout& layout) { init(span); OpenGLVtxBuffer::ConfigLayout(layout); }
    OpenGLVtxBuffer::~OpenGLVtxBuffer() { glDeleteBuffers(1, &buffer_id); }

    void OpenGLVtxBuffer::Bind() const { glBindBuffer(GL_ARRAY_BUFFER, buffer_id); }
    void OpenGLVtxBuffer::Unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }

    void OpenGLVtxBuffer::ConfigLayout(const BufferLayout& layout)
    {
        this->layout = layout;

        uint32_t idx = 0;
        for (const auto& elem : layout) {
            glEnableVertexAttribArray(idx);
            glVertexAttribPointer(
                idx,
                elem.GetElemCnt(),
                ShaderDataTypeToGLenum(elem.Type),
                elem.Normalize ? GL_TRUE : GL_FALSE,
                layout.GetStride(),
                (const void*) (uintptr_t) elem.Offset
            );
            idx++;
        }
    }

    void OpenGLVtxBuffer::init(const std::span<const float>& span_) {
        PN_CORE_ASSERT(!(span_.size() > INT32_MAX), "Element count of vertex buffer exceeds maximum GLsizei capacity of 2147483647 !!");
        elem_cnt = static_cast<uint32_t>(span_.size());

        glCreateBuffers(1, &buffer_id);
        glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
        glBufferData(GL_ARRAY_BUFFER, span_.size_bytes(), (const void*) span_.data(), GL_STATIC_DRAW);
    }
}
// ~OpenGLVtxBuffer

// INFO: belongs to OpenGLIdxBuffer
namespace PN
{
    OpenGLIdxBuffer::OpenGLIdxBuffer(std::span<const uint32_t> span)
    {
        PN_CORE_ASSERT(!(span.size() > INT32_MAX), "Element count of index buffer exceeds maximum GLsizei capacity of 2147483647 !!");
        elem_cnt = static_cast<uint32_t>(span.size());

        glCreateBuffers(1, &buffer_id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, span.size_bytes(), (const void*) span.data(), GL_STATIC_DRAW);
    }
    OpenGLIdxBuffer::~OpenGLIdxBuffer() { glDeleteBuffers(1, &buffer_id); }

    void OpenGLIdxBuffer::Bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_id); }
    void OpenGLIdxBuffer::Unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }
}
//~OpenGLIdxBuffer
