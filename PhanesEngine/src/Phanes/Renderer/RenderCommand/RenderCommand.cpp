#include "pnpch.h"
#include "RenderCommand.h"

#include "Platforms/RenderAPI/OpenGL/OpenGLRenderAPI.h"

namespace Phanes
{
    RenderAPI* RenderCmd::render_api = new OpenGLRenderAPI();
}
