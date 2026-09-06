#pragma once

#include <glad/glad.h>

#include "Phanes/Core/Renderer/Texture/Texture.h"

namespace PN
{
    class OpenGLTexture2D : public Texture2D
    {
    public:
        OpenGLTexture2D(const std::string& path);
        OpenGLTexture2D(uint32_t width, uint32_t height);
        ~OpenGLTexture2D() override;

        pn_forceinline uint32_t GetWidth() const override { return width; }
        pn_forceinline uint32_t GetHeight() const override { return height; }

        void SetData(const void *data, uint32_t size) override;

        void Bind(uint32_t slot = 0) override;
        void Unbind() override;

        const std::string& GetPath() const override { return path; }
        uint32_t GetTexId() const override { return texture_id; }
        SubTextureComp* GetSubTextureComp() const override { return nullptr; }

        bool operator==(const Texture& o) const override { return texture_id == ((const OpenGLTexture2D&) o).texture_id; }

    private:
        std::string path;
        uint32_t width = 0, height = 0;
        GLenum intern_fmt = 0, data_fmt = 0;
        uint32_t texture_id;
    };
}