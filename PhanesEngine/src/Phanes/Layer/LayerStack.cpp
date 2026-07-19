#include "pnpch.h"
#include "LayerStack.h"

namespace Phanes
{
    LayerStack::~LayerStack() { for (Layer* layer : Lys_) delete layer; }

    void LayerStack::PushLayer(Layer* layer)
    {
        Lys_.emplace(Lys_.begin() + Idx_, layer);
        layer->OnAttach(); ++Idx_;
    }
    void LayerStack::PushOverlay(Layer* overlay)
    {
        Lys_.emplace_back(overlay); 
        overlay->OnAttach();
    }

    void LayerStack::PopLayer(Layer* layer)
    {
        auto it = std::find(Lys_.begin(), Lys_.begin() + Idx_, layer);
        if (it == Lys_.end()) return;
        layer->OnDetach();
        Lys_.erase(it);
        --Idx_;
    }

    void LayerStack::PopOverlay(Layer* overlay)
    {
        auto it = std::find(Lys_.begin() + Idx_, Lys_.end(), overlay);
        if (it == Lys_.end()) return;
        overlay->OnDetach();
        Lys_.erase(it);
    }
}