#include "pnpch.h"
#include "ImGuiLayer.h"

#include "imgui.h"
#include "Platforms/OpenGL/ImGuiOpenGLRenderer.h"
#include "GLFW/glfw3.h"
#include "Phanes/Application.h"

#include <glad/glad.h>

namespace Phanes
{
    ImGuiLayer::ImGuiLayer()
        : Layer("ImGuiLayer") {}
    ImGuiLayer::~ImGuiLayer() {}

    void ImGuiLayer::OnAttach() {
        ImGui::CreateContext();
        ImGui::StyleColorsDark();

        ImGuiIO& io = ImGui::GetIO();
        io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

        ImGui_ImplOpenGL3_Init("#version 410");
    }

    void ImGuiLayer::OnDetach() {

    }

    void ImGuiLayer::OnUpdate() {
        ImGuiIO& io = ImGui::GetIO();
        Application& app = Application::Get();
        io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

        float time = (float) glfwGetTime();
        io.DeltaTime = (time_ > 0.f) ? (time - time_) : (1.f / 60.f);
        time_ = time;

        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();

        static bool show = true;
        ImGui::ShowDemoWindow(&show);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void ImGuiLayer::OnEvent(Event& e) {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<MouseButtonPressedEvent>(BIND_EVENT_FN(ImGuiLayer::OnMouseButtonPressedEvent));
        dispatcher.Dispatch<MouseButtonReleasedEvent>(BIND_EVENT_FN(ImGuiLayer::OnMouseButtonReleasedEvent));
        dispatcher.Dispatch<MouseMovedEvent>(BIND_EVENT_FN(ImGuiLayer::OnMouseMovedEvent));
        dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_FN(ImGuiLayer::OnMouseScrolledEvent));
        dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FN(ImGuiLayer::OnKeyPressedEvent));
        dispatcher.Dispatch<KeyReleasedEvent>(BIND_EVENT_FN(ImGuiLayer::OnKeyReleasedEvent));
        dispatcher.Dispatch<KeyTypedEvent>(BIND_EVENT_FN(ImGuiLayer::OnKeyTypedEvent));
        dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(ImGuiLayer::OnWindowResizeEvent));
    }

    bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e) {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseDown[e.GetButtonCode()] = true;
        return false;
    }
    bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e) {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseDown[e.GetButtonCode()] = false;
        return false;
    }
    bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent& e) {
        ImGuiIO& io = ImGui::GetIO();
        io.MousePos = ImVec2(e.GetX(), e.GetY());
        return false;
    }
    bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent& e) {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseWheelH += e.GetXOffset();
        io.MouseWheel += e.GetYOffset();
        return false;
    }
    bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& e) {
        ImGuiIO& io = ImGui::GetIO();
        io.KeysData[e.GetKeyCode()].Down = true;

        io.KeyAlt = io.KeysData[GLFW_KEY_LEFT_ALT].Down || io.KeysData[GLFW_KEY_RIGHT_ALT].Down;
        io.KeyCtrl = io.KeysData[GLFW_KEY_LEFT_CONTROL].Down || io.KeysData[GLFW_KEY_RIGHT_CONTROL].Down;
        io.KeyShift = io.KeysData[GLFW_KEY_LEFT_SHIFT].Down || io.KeysData[GLFW_KEY_RIGHT_SHIFT].Down;
        io.KeySuper = io.KeysData[GLFW_KEY_LEFT_SUPER].Down || io.KeysData[GLFW_KEY_RIGHT_SUPER].Down;

        return false;
    }
    bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& e) {
        ImGuiIO& io = ImGui::GetIO();
        io.KeysData[e.GetKeyCode()].Down = false;

        io.KeyAlt = io.KeysData[GLFW_KEY_LEFT_ALT].Down || io.KeysData[GLFW_KEY_RIGHT_ALT].Down;
        io.KeyCtrl = io.KeysData[GLFW_KEY_LEFT_CONTROL].Down || io.KeysData[GLFW_KEY_RIGHT_CONTROL].Down;
        io.KeyShift = io.KeysData[GLFW_KEY_LEFT_SHIFT].Down || io.KeysData[GLFW_KEY_RIGHT_SHIFT].Down;
        io.KeySuper = io.KeysData[GLFW_KEY_LEFT_SUPER].Down || io.KeysData[GLFW_KEY_RIGHT_SUPER].Down;

        return false;
    }
    bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& e) {
        ImGuiIO& io = ImGui::GetIO();
        int keycode = e.GetKeyCode();
        if (keycode > 0 && keycode < 0x10000)
            io.AddInputCharacter((unsigned short) keycode);

        return false;
    }
    bool ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent& e) {
        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize = ImVec2((float) e.GetWidth(), (float) e.GetHeight());
        io.DisplayFramebufferScale = ImVec2(1.f, 1.f);
        glViewport(0, 0, e.GetWidth(), e.GetHeight());

        return false;
    }
}