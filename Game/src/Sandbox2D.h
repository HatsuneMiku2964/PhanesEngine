#pragma once

#include <Phanes.h>

class Sandbox2D : public PN::Layer
{
public:
    Sandbox2D();
    ~Sandbox2D() override = default;

    void OnAttach() override;
    void OnDetach() override;

    void OnUpdate(PN::TimeStep ts) override;
    void OnEvent(PN::Event& event) override;
    void OnImGuiRender() override;

private:
    PN::OrthoCameraController camera_ctrl;

    PN::Ref<PN::VtxArr> vao;
    PN::Ref<PN::Shader> shader;
    PN::Ref<PN::Texture2D> tex;

    glm::vec3 color = {0.2f, 0.1f, 1.f};
};

