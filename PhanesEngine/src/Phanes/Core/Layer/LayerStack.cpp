#include "pnpch.h"

#include "LayerStack.h"

namespace PN
{
    LayerStack::~LayerStack() { PROFILE_FN(); for (Layer* layer : Layers_) { layer->OnDetach(); delete layer; } }

    void LayerStack::PushLayer(Layer* layer)
    {
        Layers_.emplace(Layers_.begin() + Idx_, layer);
        layer->OnAttach(); ++Idx_;
    }
    void LayerStack::PushOverlay(Layer* overlay)
    {
        Layers_.emplace_back(overlay);
        overlay->OnAttach();
    }

    void LayerStack::PopLayer(Layer* layer)
    {
        auto it = std::find(Layers_.begin(), Layers_.begin() + Idx_, layer);
        if (it == Layers_.end()) return;
        layer->OnDetach();
        Layers_.erase(it);
        --Idx_;
    }

    void LayerStack::PopOverlay(Layer* overlay)
    {
        auto it = std::find(Layers_.begin() + Idx_, Layers_.end(), overlay);
        if (it == Layers_.end()) return;
        overlay->OnDetach();
        Layers_.erase(it);
    }
}