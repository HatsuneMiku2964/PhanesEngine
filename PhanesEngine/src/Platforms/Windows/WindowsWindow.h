#pragma once

#include <GLFW/glfw3.h>

#include "Phanes/Window.h"
#include "Phanes/Renderer/RenderContext.h"

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
        pn_forceinline bool IsVSync() const override;
        pn_forceinline void* GetNativeWindow() const override { return (void*)window_; }
        pn_forceinline uint32_t GetWidth() const override { return data_.Width; }
        pn_forceinline uint32_t GetHeight() const override { return data_.Height; }

        // util setters & impls
        pn_forceinline void SetVSync(bool enabled) override;
        pn_forceinline void SetEventCallback(const EventCallbackFn& callback) override { data_.EventCallback = callback; }

    private:
        virtual void Init(const WindowProps& props);
        virtual void Shutdown();

    private:
        GLFWwindow* window_;
        std::unique_ptr<RenderContext> context_;

        // main attributes of the window
        struct WindowData
        {
            std::string Title;
            uint32_t Width, Height;
            bool VSync;
            EventCallbackFn EventCallback;
        };

        WindowData data_;
    };
}