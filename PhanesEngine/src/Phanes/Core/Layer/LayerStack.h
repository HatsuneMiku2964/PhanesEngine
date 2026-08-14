#pragma once

#include "Layer.h"

namespace PN
{
    class LayerStack
    {
    public:
        LayerStack() : Idx_(0) { PROFILE_FN(); }
        ~LayerStack();
        
        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);
        void PopLayer(Layer* layer);
        void PopOverlay(Layer* overlay);

        pn_forceinline std::vector<Layer*>::iterator begin() noexcept { return Layers_.begin(); }
        pn_forceinline std::vector<Layer*>::iterator end() noexcept { return Layers_.end(); }
        pn_forceinline std::vector<Layer*>::const_iterator begin() const noexcept { return Layers_.begin(); }
        pn_forceinline std::vector<Layer*>::const_iterator end() const noexcept { return Layers_.end(); }
        pn_forceinline size_t size() const noexcept { return Layers_.size(); }

    protected:
        std::vector<Layer*> Layers_;
        uint32_t Idx_;
    };
}