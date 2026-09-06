#pragma once

namespace PN
{
    class Texture2D;
    struct SubTextureComp;

    class SubTexture2D
    {
    public:
        virtual Ref<Texture2D> GetSourceTex() const = 0;

        static Ref<SubTexture2D> Create(const Texture2D& texture, const SubTextureComp& data);
    };
}