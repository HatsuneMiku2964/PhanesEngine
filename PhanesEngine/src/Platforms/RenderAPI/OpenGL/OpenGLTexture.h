#pragma once

#include "Phanes/Core/Renderer/Texture/Texture.h"

namespace PN
{
    class OpenGLTexture2D : public Texture2D
    {
    public:
        OpenGLTexture2D(const std::string& path);
        ~OpenGLTexture2D() override;

        pn_forceinline uint32_t GetWidth() const override { return width; }
        pn_forceinline uint32_t GetHeight() const override { return height; }

        void Bind(uint32_t slot = 0) override;
        void Unbind() override;

    private:
        std::string path;
        uint32_t width = 0, height = 0;
        uint32_t texture_id;
    };
}