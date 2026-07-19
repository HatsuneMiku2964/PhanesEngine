#pragma once

#include "Phanes/Layer/Layer.h"

#include "Phanes/Events/KeyEvents.h"
#include "Phanes/Events/MouseEvents.h"
#include "Phanes/Events/AppEvents.h"

namespace Phanes
{
    class PN_API ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer() override;

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnImGuiRender() override;

        void Begin();
        void End();

    private:
        float time_ = 0.f;
    };
}