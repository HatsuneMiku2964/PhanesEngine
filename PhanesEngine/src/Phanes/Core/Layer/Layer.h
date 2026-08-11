#pragma once

#include "Phanes/Core/Events/Events.h"
#include "Phanes/Core/TimeStep/TimeStep.h"

namespace PN
{
    class Layer
    {
    public:
        Layer(const std::string& name = "Layer") : DebugName_(name) {}
        virtual ~Layer() = default;

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate(TimeStep ts) {}
        virtual void OnImGuiRender() {}
        virtual void OnEvent(Event& event) {}

        pn_forceinline const std::string& GetName() const { return DebugName_; }
    protected:
        std::string DebugName_;
    };
}