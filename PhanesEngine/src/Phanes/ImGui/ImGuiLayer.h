#pragma once

#include "Phanes/Layer/Layer.h"

#include "Phanes/Events/KeyEvents.h"
#include "Phanes/Events/MouseEvents.h"
#include "Phanes/Events/AppEvents.h"

namespace Phanes
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