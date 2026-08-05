#pragma once

#include <span>

namespace PN
{
    namespace ShaderData
    {
        enum class ShaderDataType : uint8_t
        {
            None = 0,
            Float, Float2, Float3, Float4,
            Mat3, Mat4,
            Int, Int2, Int3, Int4,
        };

        pn_forceinline static uint32_t ShaderDataTypeSize(const ShaderDataType& type)
        {
            switch (type) {
            case ShaderDataType::Float:     return 4;
            case ShaderDataType::Float2:    return 4 * 2;
            case ShaderDataType::Float3:    return 4 * 3;
            case ShaderDataType::Float4:    return 4 * 4;
            case ShaderDataType::Mat3:      return 4 * 3 * 3;
            case ShaderDataType::Mat4:      return 4 * 4 * 4;
            case ShaderDataType::Int:       return 4;
            case ShaderDataType::Int2:      return 4 * 2;
            case ShaderDataType::Int3:      return 4 * 3;
            case ShaderDataType::Int4:      return 4 * 4;

            case ShaderDataType::None:  PN_CORE_LOG_ERROR("Invalid shader data type of \"None\"");  return 0;
            default:                    PN_CORE_LOG_ERROR("Unknown shader data type!!");            return 0;
            }
        }
    }

    struct BufferLayout_Elem
    {
        BufferLayout_Elem(const ShaderData::ShaderDataType& type)
            : Size(ShaderData::ShaderDataTypeSize(type)), Type(type), Normalize(false), Offset(0)
        {
        }

        uint32_t Size;
        ShaderData::ShaderDataType Type;
        uint32_t Normalize;
        uint32_t Offset;

        pn_forceinline uint32_t GetElemCnt() const
        {
            switch (Type) {
                case ShaderData::ShaderDataType::Float:     return 1;
                case ShaderData::ShaderDataType::Float2:    return 2;
                case ShaderData::ShaderDataType::Float3:    return 3;
                case ShaderData::ShaderDataType::Float4:    return 4;
                case ShaderData::ShaderDataType::Mat3:      return 3 * 3;
                case ShaderData::ShaderDataType::Mat4:      return 4 * 4;
                case ShaderData::ShaderDataType::Int:       return 1;
                case ShaderData::ShaderDataType::Int2:      return 2;
                case ShaderData::ShaderDataType::Int3:      return 3;
                case ShaderData::ShaderDataType::Int4:      return 4;

                case ShaderData::ShaderDataType::None: PN_CORE_LOG_ERROR("Invalid shader data type of \"None\"");  return 0;
                default:                               PN_CORE_LOG_ERROR("Unknown shader data type!!");            return 0;
            }
        }
    };
    struct BufferLayout
    {
    public:
        BufferLayout(const std::initializer_list<BufferLayout_Elem>& elements)
            : elements(elements)
        {
            uint32_t offset = 0;
            for (auto& elem : this->elements) {
                elem.Offset = offset;
                offset += elem.Size;
                stride += elem.Size;
            }
        }

        // INFO: enables BufferLayout to be used (kind of) as a vector
        pn_forceinline std::vector<BufferLayout_Elem>::iterator begin() noexcept { return elements.begin(); }
        pn_forceinline std::vector<BufferLayout_Elem>::iterator end() noexcept { return elements.end(); }
        pn_forceinline std::vector<BufferLayout_Elem>::const_iterator begin() const noexcept { return elements.cbegin(); }
        pn_forceinline std::vector<BufferLayout_Elem>::const_iterator end() const noexcept { return elements.cend(); }

        pn_forceinline size_t size() const noexcept { return elements.size(); }
        pn_forceinline BufferLayout_Elem operator[](uint32_t idx) const noexcept { return elements[idx]; }
        // ~~~

        pn_forceinline const std::vector<BufferLayout_Elem>& GetElements() const { return elements; }
        pn_forceinline uint32_t GetStride() const { return stride; }

    private:
        std::vector<BufferLayout_Elem> elements;
        uint32_t stride = 0;
    };

    class VtxBuffer
    {
    public:
        virtual ~VtxBuffer() {}

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void ConfigLayout(const BufferLayout& layout) = 0;

        virtual const BufferLayout& GetLayout() const = 0;
        virtual uint32_t GetCount() const = 0;

        static VtxBuffer* Create(std::span<const float> vertices);
        static VtxBuffer* Create(std::span<const float> vertices, const BufferLayout& layout);
    };
    class IdxBuffer
    {
    public:
        virtual ~IdxBuffer() {}

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual uint32_t GetCount() const = 0;

        static IdxBuffer* Create(std::span<const uint32_t> indices);
    };
}
