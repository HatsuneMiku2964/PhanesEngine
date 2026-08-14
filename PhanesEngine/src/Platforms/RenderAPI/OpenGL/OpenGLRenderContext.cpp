#include "pnpch.h"
#include "OpenGLRenderContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace PN
{
    OpenGLRenderContext::OpenGLRenderContext(GLFWwindow* window) : window_handle(window) { PN_CORE_ASSERT(window, "window handle is invalid!!"); }

    bool OpenGLRenderContext::Init()
    {
        PROFILE_FN()

        glfwMakeContextCurrent(window_handle);
        int status = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
        PN_CORE_ASSERT(status, "Failed to initialize Glad!");

        PN_CORE_LOG_INFO("OpenGL info: ");
        PN_CORE_LOG_INFO("    vendor:   {0}", (const char*) glGetString(GL_VENDOR));
        PN_CORE_LOG_INFO("    renderer: {0}", (const char*) glGetString(GL_RENDERER));
        PN_CORE_LOG_INFO("    version:  {0}", (const char*) glGetString(GL_VERSION));

        int version_maj, version_min;
        glGetIntegerv(GL_MAJOR_VERSION, &version_maj);
        glGetIntegerv(GL_MINOR_VERSION, &version_min);
        PN_CORE_ASSERT(version_maj > 4 || (version_maj == 4 && version_min >= 5), "Phanes requires a OpenGL for at least version 4.5!!");

        return (bool) status;
    }

    bool OpenGLRenderContext::Swap()
    {
        glfwSwapBuffers(window_handle);
        return true;
    }
}
