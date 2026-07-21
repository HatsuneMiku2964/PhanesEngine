#pragma once

#include <GLFW/glfw3.h>

#include "Phanes/Window.h"
#include "Renderer/RenderContext.h"

namespace Phanes
{
    class WindowsWindow : public Window
    {
    public:
        WindowsWindow(const WindowProps& props);
        ~WindowsWindow() override;

        // main loop impl
        void OnUpdate() override;

        // util getters & impls
        bool IsVSync() const override;
        inline virtual void* GetNativeWindow() const override { return (void*)window_; }
        inline unsigned int GetWidth() const override { return data_.Width; }
        inline unsigned int GetHeight() const override { return data_.Height; }

        // util setters & impls
        void SetVSync(bool enabled) override;
        inline void SetEventCallback(const EventCallbackFn& callback) override { data_.EventCallback = callback; }

    private:
        virtual void Init(const WindowProps& props);
        virtual void Shutdown();

    private:
        GLFWwindow* window_;
        RenderContext* context_;

        // main attributes of the window
        struct WindowData
        {
            std::string Title;
            unsigned int Width, Height;
            bool VSync;
            EventCallbackFn EventCallback;
        };

        WindowData data_;
    };
}