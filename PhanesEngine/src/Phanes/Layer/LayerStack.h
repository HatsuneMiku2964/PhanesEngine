#pragma once

#include "Layer.h"

namespace Phanes
{
    class LayerStack
    {
    public:
        LayerStack() : Idx_(0) {}
        ~LayerStack();
        
        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);
        void PopLayer(Layer* layer);
        void PopOverlay(Layer* overlay);

        pn_forceinline std::vector<Layer*>::iterator begin() { return Lys_.begin(); }
        pn_forceinline std::vector<Layer*>::iterator end() { return Lys_.end(); }

    protected:
        std::vector<Layer*> Lys_;	// the actual stack
        uint32_t Idx_;			/* INFO: the index of the last layer (not overlays, the first half),
                                            this is to make sure that layers & overlays are inserted properly */
    };
}