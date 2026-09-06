#include "pnpch.h"
#include "OpenGLSubTexture2D.h"

namespace PN
{
    OpenGLSubTexture2D::OpenGLSubTexture2D(const Texture2D& texture, SubTextureComp& comp) 
        : OpenGLTexture2D(texture.GetPath()), comp(&comp) {}
}
