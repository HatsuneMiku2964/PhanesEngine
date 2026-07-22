#include "pnpch.h"
#include "OpenGLRenderContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Phanes
{
    OpenGLRenderContext::OpenGLRenderContext(GLFWwindow* window) : window_handle(window) { PN_CORE_ASSERT(window, "window handle is NULL!!"); }

    bool OpenGLRenderContext::Init()
    {
        glfwMakeContextCurrent(window_handle);
        int status = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
        PN_CORE_ASSERT(status, "Failed to initialize Glad!");

        PN_CORE_LOG_INFO("OpenGL info: ");
        PN_CORE_LOG_INFO("    vendor:   {0}", (const char*) glGetString(GL_VENDOR));
        PN_CORE_LOG_INFO("    renderer: {0}", (const char*) glGetString(GL_RENDERER));
        PN_CORE_LOG_INFO("    version:  {0}", (const char*) glGetString(GL_VERSION));

        return (bool) status;
    }

    bool OpenGLRenderContext::Swap()
    {
        glfwSwapBuffers(window_handle);
        return true;
    }
}
