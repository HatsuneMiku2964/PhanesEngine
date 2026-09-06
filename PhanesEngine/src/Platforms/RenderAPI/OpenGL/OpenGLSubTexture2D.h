#pragma once

#include "OpenGLTexture.h"
#include "Phanes/Core/Renderer/Texture/SubTexture2D.h"

namespace PN
{
    class OpenGLSubTexture2D : public OpenGLTexture2D, public SubTexture2D
    {
    public:
        OpenGLSubTexture2D(const Texture2D& texture, SubTextureComp& comp);

        SubTextureComp* GetSubTextureComp() const override { return comp; }
        Ref<Texture2D> GetSourceTex() const override { return SrcTex; }

    private:
        SubTextureComp* comp;
        Ref<Texture2D> SrcTex;
    };
}
