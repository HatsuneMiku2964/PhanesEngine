#include "pnpch.h"
#include "OpenGLTexture.h"

#include <stb_image.h>

namespace PN
{
    OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
        : path(path)
    {
        int width, height, channels;
        stbi_set_flip_vertically_on_load(1);
        stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
        PN_CORE_ASSERT(data, "Failed to load image from path \"{0}\"", path.c_str());

        this->width = width;
        this->height = height;

        GLenum intern_fmt = 0, data_fmt = 0;
        if (channels == 4) {
            intern_fmt = GL_RGBA8;
            data_fmt = GL_RGBA;
        } else if (channels == 3) {
            intern_fmt = GL_RGB8;
            data_fmt = GL_RGB;
        }
        this->intern_fmt = intern_fmt;
        this->data_fmt = data_fmt;

        PN_CORE_ASSERT(intern_fmt & data_fmt, "invalid image format!!");

        glCreateTextures(GL_TEXTURE_2D, 1, &texture_id);
        glTextureStorage2D(texture_id, 1, intern_fmt, width, height);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTextureSubImage2D(texture_id, 0, 0, 0, width, height, data_fmt, GL_UNSIGNED_BYTE, data);
        glBindTexture(GL_TEXTURE_2D, 0);

        if (data) stbi_image_free(data);
    }
    OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height)
        : width(width), height(height)
    {
        GLenum intern_fmt = GL_RGBA8, data_fmt = GL_RGBA;
        this->intern_fmt = intern_fmt;
        this->data_fmt = data_fmt;

        PN_CORE_ASSERT(intern_fmt & data_fmt, "invalid image format!!");

        glCreateTextures(GL_TEXTURE_2D, 1, &texture_id);
        glTextureStorage2D(texture_id, 1, intern_fmt, width, height);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }
    OpenGLTexture2D::~OpenGLTexture2D() { glDeleteTextures(1, &texture_id); }

    void OpenGLTexture2D::SetData(void* data, uint32_t size)
    {
        uint32_t bpp = (data_fmt == GL_RGBA) ? 4 : 3;
        PN_CORE_ASSERT(size == width * height * bpp, "data must be entirely a texture!!");
        glTextureSubImage2D(texture_id, 0, 0, 0, width, height, data_fmt, GL_UNSIGNED_BYTE, data);
    }

    void OpenGLTexture2D::Bind(uint32_t slot) { glBindTextureUnit(slot, texture_id); }
    void OpenGLTexture2D::Unbind() { glBindTexture(GL_TEXTURE_2D, 0); }
}
