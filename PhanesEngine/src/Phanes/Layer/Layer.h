#pragma once

#include "Phanes/Core.h"
#include "Phanes/Events/Events.h"

namespace Phanes
{
    class Layer
    {
    public:
        Layer(const std::string& name = "Layer");
        virtual ~Layer();

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