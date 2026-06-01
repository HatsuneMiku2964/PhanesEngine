#include "pnpch.h"
#include "LayerStack.h"

namespace Phanes {
	LayerStack::LayerStack()
	{
		LayerInsert_ = Layers_.begin();
	}

	LayerStack::~LayerStack()
	{
		for (Layer* layer : Layers_) delete layer;
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		LayerInsert_ = Layers_.emplace(LayerInsert_, layer);
	}

	void LayerStack::PushOverlay(Layer* overlay)
	{
		Layers_.emplace_back(overlay);
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(Layers_.begin(), Layers_.end(), layer);
		if (it != Layers_.end()) {
			Layers_.erase(it);
			LayerInsert_--;
		}
	}

	void LayerStack::PopOverlay(Layer* overlay)
	{
		auto it = std::find(Layers_.begin(), Layers_.end(), overlay);
		if (it != Layers_.end()) Layers_.erase(it);
	}
}