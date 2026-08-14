#include "pnpch.h"
#include "WindowsWindow.h"

#include "Phanes/Core/Events/AppEvents.h"
#include "Phanes/Core/Events/KeyEvents.h"
#include "Phanes/Core/Events/MouseEvents.h"
#include "Platforms/RenderAPI/OpenGL/OpenGLRenderContext.h"

namespace PN
{
    static bool GLFWInitialized = false;
    static void GLFWErrorCallback(int error, const char* description) { PN_CORE_LOG_ERROR("GLFW Error ({0}): {1}", error, description); }

    Window* Window::Create(const WindowProps& props) { return new WindowsWindow(props); }

    WindowsWindow::WindowsWindow(const WindowProps& props) { WindowsWindow::Init(props); }
    WindowsWindow::~WindowsWindow() { WindowsWindow::Shutdown(); }

    void WindowsWindow::OnUpdate()
    {
        glfwPollEvents();
        context_->Swap();
    }

    void WindowsWindow::SetVSync(bool enabled)
    {
        PROFILE_FN();
        data.VSync = enabled;

        if (enabled)    glfwSwapInterval(1);
        else            glfwSwapInterval(0);
    }

    void WindowsWindow::Init(const WindowProps& props)
    {
        PROFILE_FN();

        data.Width = props.Width;
        data.Height = props.Height;
        data.Title = props.Title;

        PN_CORE_LOG_INFO("Creating window: Title: {0}, size = {1}px * {2}px", props.Title, props.Width, props.Height);

        if (!GLFWInitialized) 
        {
            PROFILE_SCOPE("glfwInit");
            int success = glfwInit();
            PN_CORE_ASSERT(success, "Could not initialize GLFW!");
            glfwSetErrorCallback(GLFWErrorCallback);
            GLFWInitialized = true;
        }

        {
            PROFILE_SCOPE("glfwCreateWindow");
            window_ = glfwCreateWindow((int) props.Width, (int) props.Height, data.Title.c_str(), nullptr, nullptr);
        }
        context_.reset(new OpenGLRenderContext(window_));
        context_->Init();

        glfwSetWindowUserPointer(window_, &data);
        SetVSync(true);

        // Set GLFW callbacks
        glfwSetWindowSizeCallback(window_, [](GLFWwindow* window, int width, int height) {
            WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);
            data.Width = width;
            data.Height = height;

            WindowResizeEvent event(width, height);
            data.EventFn(event);// at this time this callback is already set up
        });
        glfwSetWindowCloseCallback(window_, [](GLFWwindow* window) {
            WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);
            WindowCloseEvent event;
            data.EventFn(event);
        });
        glfwSetKeyCallback(window_, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
            WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);
            switch (action) {
            case GLFW_PRESS:
            {
                KeyPressedEvent event(key, 0);
                data.EventFn(event);
                break;
            }
            case GLFW_RELEASE:
            {
                KeyReleasedEvent event(key);
                data.EventFn(event);
                break;
            }
            case GLFW_REPEAT:
            {
                KeyPressedEvent event(key, 1);
                data.EventFn(event);
                break;
            }
            default: PN_CORE_ASSERT(false, "Unknown key action of {0}!!", action);
            }
        });
        glfwSetCharCallback(window_, [](GLFWwindow* window, uint32_t key) {
            WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);
            KeyTypedEvent event(key);
            data.EventFn(event);
        });
        glfwSetMouseButtonCallback(window_, [](GLFWwindow* window, int button, int action, int mods) {
            WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);
            switch (action) {
            case GLFW_PRESS:
            {
                MouseButtonPressedEvent event(button);
                data.EventFn(event);
                break;
            }
            case GLFW_RELEASE:
            {
                MouseButtonReleasedEvent event(button);
                data.EventFn(event);
                break;
            }
            }
        });
        glfwSetScrollCallback(window_, [](GLFWwindow* window, double xOffset, double yOffset) {
            WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);
            MouseScrolledEvent event((float) xOffset, (float) yOffset);
            data.EventFn(event);
        });
        glfwSetCursorPosCallback(window_, [](GLFWwindow* window, double xPos, double yPos) {
            WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);
            MouseMovedEvent event((float) xPos, (float) yPos);
            data.EventFn(event);
        });
        // ~Set GLFW callbacks
    }

    void WindowsWindow::Shutdown()
    {
        PROFILE_FN(); 
        glfwDestroyWindow(window_); 
    }
};