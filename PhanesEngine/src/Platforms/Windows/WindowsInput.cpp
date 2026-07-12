#include "pnpch.h"
#include "WindowsInput.h"

#include <GLFW/glfw3.h>

#include "Phanes/App/Application.h"

namespace Phanes
{
    Input* Input::instance_ = new WindowsInput();
    
    bool WindowsInput::IsKeyPressed_Impl(int keycode)
    {
        GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        int state = glfwGetKey(window, keycode);
        return (state == GLFW_PRESS) || (state == GLFW_REPEAT);
    }

    bool WindowsInput::IsMouseButtonPressed_Impl(int button)
    {
        GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        int state = glfwGetMouseButton(window, button);
        return state == GLFW_PRESS;
    }

    float WindowsInput::GetMouseX_Impl()
    {
        auto [x, y] = WindowsInput::GetMousePos_Impl();
        return x;
    }

    float WindowsInput::GetMouseY_Impl()
    {
        auto [x, y] = WindowsInput::GetMousePos_Impl();
        return y;
    }

    std::pair<float, float> WindowsInput::GetMousePos_Impl() {
        GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        std::pair<double, double> pos;
        glfwGetCursorPos(window, &pos.first, &pos.second);
        return {(float)pos.first, (float)pos.second};
    }
}
