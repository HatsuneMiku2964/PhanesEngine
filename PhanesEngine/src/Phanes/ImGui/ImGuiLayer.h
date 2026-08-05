#pragma once

#include "Phanes/Core/Layer/Layer.h"

namespace PN
{
    class ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer() override;

        void OnAttach() override;
        void OnDetach() override;
        void OnImGuiRender() override;

        void Begin();
        void End();

    private:
        float time_ = 0.f;
    };
}