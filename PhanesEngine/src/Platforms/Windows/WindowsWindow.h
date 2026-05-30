#pragma once

#include "Phanes/Window.h"
#include <GLFW/glfw3.h>

namespace Phanes {
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		// main loop impl
		void OnUpdate() override;

		// util getters & impls
		inline unsigned int GetWidth() const override { return Data__.Width; }
		inline unsigned int GetHeight() const override { return Data__.Height; }
		bool IsVSync() const override;

		// util setters & impls
		inline void SetEventCallback(const EventCallbackFn& callback) override { Data__.EventCallback = callback; }
		void SetVSync(bool enabled) override;

	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();
	private:
		GLFWwindow* Window__;

		// main attribute set of the window
		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;
			EventCallbackFn EventCallback;
		};

		WindowData Data__;
	};
}